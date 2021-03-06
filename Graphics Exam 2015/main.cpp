//===========================================================
// File: main.cpp	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================

/* Template Author:Simon McCallum
Notes:
Created for the IMT2531 Graphics Exam 2015

To get the naming right I have set.
Project-> Properties -> Configuration properties -> General -> Target name  = exam2015.exe
Project-> Properties -> Configuration properties -> Debugging -> Commande Arguments = terrain.pnm

I suggest you read and understand how the input handler works.  It uses and event queue system.
The keyboard events create game events which are pushed onto the GameEvent queue.  These are the
events which the program should actually repond to rather than the actual keyboard presses.

You should have environment variables set up for home of SDL GLEW and GLM so the calls below work
$(SDL_HOME)\include;$(GLEW_HOME)\include;$(GLM_HOME);$(IncludePath)


*/

#define GLM_FORCE_RADIANS //Using degrees with glm is deprecated.
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <random>

#include "GameEvent.h"
#include "InputHandler.h"

#include "Camera.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "TerrainHandler.h"
#include "Consts.h"


// Force external GPU
// As my PC Sometimes decides 
//extern "C"
//{
//    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//}


std::vector<std::vector<int>> LoadTerrain(const std::string& terrainFilename)
{
    std::ifstream inputFile(terrainFilename);
    std::stringstream lineStream;
    std::string inputLine;

    std::getline(inputFile, inputLine);

    if (inputLine.compare("P2") != 0)
    {
        std::cerr << "Version error" << std::endl;
    }
    else
    {
        std::cout << "Version : " << inputLine << std::endl;
    }

    std::vector<std::vector<int>> positions;
    int xSize = 0;
    int ySize = 0;
    int maxValue = 0;
    inputFile >> xSize >> ySize >> maxValue;

    positions.resize(xSize);
    for (std::size_t i = 0; i < xSize; ++i)
    {
        positions[i].resize(ySize);
    }

    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        for (std::size_t j = 0; j < positions[i].size(); ++j)
        {
            inputFile >> positions[i][j];
            positions[i][j] += 1;
        }
    }

    return positions;
}

gsl::owner<SceneObject*> createSkyBox(Renderer& renderer)
{
    constexpr float skyboxScale = 1000.0f;
    SceneObject* skyBox = new SceneObject(renderer,
                                          Renderer::nonScalingShader,
                                          Renderer::cubeMesh,
                                          Renderer::skyboxDayTexture,
                                          0,
                                          glm::vec3(0.0f, 0.0f, 0.0f),
                                          glm::vec3(skyboxScale, skyboxScale, skyboxScale),
                                          glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                          glm::vec3(0.0f, 0.0f, 0.0f),
                                          Renderer::FacingDirection::FRONT);
    return skyBox;
}

std::tuple<bool, std::size_t, std::size_t> calculateCameraPositionInGrid(const std::vector<std::vector<int>>& heightMap,
                                                                         const Camera& camera) noexcept
{
    // Calculate into index space,
    std::size_t cameraPositionIndexSpaceX = static_cast<std::size_t>((camera.getPosition().x + (SceneObject::cubeSize / 2)) / SceneObject::cubeSize);
    std::size_t cameraPositionIndexSpaceZ = static_cast<std::size_t>((camera.getPosition().z + (SceneObject::cubeSize / 2)) / SceneObject::cubeSize);

    if (cameraPositionIndexSpaceX >= 0 &&
        cameraPositionIndexSpaceX < heightMap.size())
    {
        if (cameraPositionIndexSpaceZ >= 0 &&
            cameraPositionIndexSpaceZ < heightMap[cameraPositionIndexSpaceX].size())
        {
            auto indexCoordinates = std::make_tuple(true, cameraPositionIndexSpaceX, cameraPositionIndexSpaceZ);
            return indexCoordinates;
        }
    }
    auto indexCoordinates = std::make_tuple(false, cameraPositionIndexSpaceX, cameraPositionIndexSpaceZ);
    return indexCoordinates;
}

// Not nice function call, I know :/
void handleInput(std::queue<GameEvent>& eventQueue,
                 Renderer& renderer,
                 Camera& camera,
                 float deltaTime,
                 glm::vec2& mousePosition,
                 const std::vector<std::vector<int>>& heightMap,
                 TerrainHandler& terrainHandler) noexcept
{
    static bool enableMovement = false;
    while (!eventQueue.empty())
    {
        GameEvent nextEvent = eventQueue.front();
        eventQueue.pop();

        switch (nextEvent.action)
        {
        case ActionEnum::RAISE:
            renderer.increaseWorldScale();
            break;

        case ActionEnum::LOWER:
            renderer.decreaseWorldScale();
            break;

        case ActionEnum::RESET:
            renderer.resetWorldScale();
            break;

        case ActionEnum::LATER:
            renderer.advanceLight(deltaTime);
            break;

        case ActionEnum::EARLIER:
            renderer.regressLight(deltaTime);
            break;

        case ActionEnum::FORWARD:
            if (enableMovement)
            {
                camera.moveForward(deltaTime);
            }
            break;

        case ActionEnum::BACK:
            if (enableMovement)
            {
                camera.moveBack(deltaTime);
            }
            break;

        case ActionEnum::LEFT:
            if (enableMovement)
            {
                camera.strafeLeft(deltaTime);
            }
            break;

        case ActionEnum::RIGHT:
            if (enableMovement)
            {
                camera.strafeRight(deltaTime);
            }
            break;

        case ActionEnum::DOWN:
            if (enableMovement)
            {
                camera.moveDown(deltaTime);
            }
            break;

        case ActionEnum::UP:
            if (enableMovement)
            {
                camera.moveUp(deltaTime);
            }
            break;

        case ActionEnum::MOUSEMOTION:
            if (enableMovement)
            {
                camera.rotateCamera(mousePosition);
            }
            break;

        case ActionEnum::ENABLEMOVEMENT:
            enableMovement = !enableMovement;
            break;

        case ActionEnum::CREATE:
        {
            auto calculationResult = calculateCameraPositionInGrid(heightMap, camera);
            if (std::get<0>(calculationResult))
            {
                terrainHandler.addCube(std::get<1>(calculationResult), std::get<2>(calculationResult));
            }
        }
        break;

        case ActionEnum::DESTROY:
        {
            auto calculationResult = calculateCameraPositionInGrid(heightMap, camera);
            if (std::get<0>(calculationResult))
            {
                terrainHandler.deleteCube(std::get<1>(calculationResult), std::get<2>(calculationResult));
            }
        }
        break;

        case ActionEnum::NEXTTEXTURE:
            terrainHandler.switchToNextTextureSet();
            break;

        case ActionEnum::TOGGLERAIN:
            terrainHandler.toggleRain();
            break;

        case ActionEnum::TOGGLESNOW:
            terrainHandler.toggleSnow();
            break;

        case ActionEnum::TOGGLEWARPMODE:
            renderer.toggleWarpMode();
        }
    }
}



void handleTimeOfDay(Renderer& renderer, SceneObject& skyBox)
{
    if (renderer.isDayTime())
    {

        skyBox.setTexture(Renderer::skyboxDayTexture);
        return;
    }
    skyBox.setTexture(Renderer::skyboxNightTexture);
}

int main(int argc, char* argv[])
{
    Camera camera;
    Renderer renderer(Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, camera);

    if (!renderer.initialize())
    {
        std::cout << "Could not initialize openGL" << std::endl;
        std::exit(-1);
    }

    std::vector<std::vector<int>> heights;
    if (argc > 1)
    {
        heights = LoadTerrain(std::string(argv[1]));
    }
    else
    {
    // Performance is horrible on debug with terrain3.
    #ifdef _DEBUG
        heights = LoadTerrain("../terrain.pnm");
    #else
        heights = LoadTerrain("../terrain3.pnm");
    #endif
    }

    SDL_Event eventHandler;
    InputHandler inputHandler;
    std::queue<GameEvent> eventQueue;
    glm::vec2 mousePosition;
    TerrainHandler terrainHandler(renderer, heights);

    auto skyBox = createSkyBox(renderer);
    // 0.1 as we don't want to multiply our scales etc with 0 on first runthrough
    float deltaTime = 0.1f;
    while (renderer.windowIsOpen())
    {
        bool keepWindowOpen = inputHandler.processEvents(eventHandler, eventQueue, mousePosition);

        auto clockStart = std::chrono::high_resolution_clock::now();
        camera.update(deltaTime);

        renderer.keepWindowOpen(keepWindowOpen);
        renderer.clear();

        terrainHandler.update(deltaTime);
        skyBox->update(deltaTime);
        skyBox->draw();

        renderer.present();
        handleInput(eventQueue, renderer, camera, deltaTime, mousePosition, heights, terrainHandler);

        auto clockStop = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(clockStop - clockStart).count();


        handleTimeOfDay(renderer, *skyBox);
    }
    delete skyBox;
    return 0;
}