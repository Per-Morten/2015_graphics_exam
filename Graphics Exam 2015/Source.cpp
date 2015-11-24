#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

#include "GameEvent.h"
#include "InputHandler.h"

#include "Camera.h"
#include "Renderer.h"
#include "SceneObject.h"

// Force external GPU
// As my PC Sometimes decides 
extern "C"
{
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
std::string windowName = "Graphics Exam 2015 - Per-Morten Straume";

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
        for (std::size_t j = 0; j < positions.size(); ++j)
        {
            inputFile >> positions[i][j];
            positions[i][j] += 1;
        }
    }

    return positions;
}

std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>> createCubes(Renderer& renderer, std::vector<std::vector<int>> heights)
{
    std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>> objects;

    objects.resize(heights.size());

    for (std::size_t i = 0; i < heights.size(); ++i)
    {
        objects[i].resize(heights[i].size());

        for (std::size_t j = 0; j < heights[i].size(); ++j)
        {
            for (int k = 0; k < heights[i][j]; ++k)
            {
                glm::vec2 textureOffset;
                if (k < 2)
                {
                    textureOffset = glm::vec2(3.0f/4.0f, 0.0f);
                }
                else if (k < 3)
                {
                    textureOffset = glm::vec2(0.0f, 0.0f);
                }
                else if (k < 18)
                {
                    textureOffset = glm::vec2(1.0f/4.0f, 0.0f);
                }
                else if (k < 21)
                {
                    textureOffset = glm::vec2(2.0f/4.0f, 0.0f);
                }
                SceneObject* object = new SceneObject(renderer,
                                                      "DirectionalFullTexture",
                                                      "Cube",
                                                      "Bricks",
                                                      glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                                      glm::vec3(i * 10, k * 10.0f, j * 10),
                                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      textureOffset);
                objects[i][j].push_back(object);

            }
        }
    }

    return objects;
}

std::vector<gsl::owner<SceneObject*>> createCubes1D(Renderer& renderer, std::vector<std::vector<int>> heights)
{
    std::vector<gsl::owner<SceneObject*>> cubes;

    for (std::size_t i = 0; i < heights.size(); ++i)
    {
        for (std::size_t j = 0; j < heights[i].size(); ++j)
        {
            for (int k = 0; k < heights[i][j]; ++k)
            {
                SceneObject* object = new SceneObject(renderer,
                                                      "DirectionalFullTexture",
                                                      "Cube",
                                                      "Bricks",
                                                      glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                                      glm::vec3(i * 10, k * 10.0f, j * 10),
                                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                                      glm::vec3(1.0f, 1.0f, 1.0f));
                cubes.push_back(object);
            }
        }
    }
    return cubes;
}



int main(int argc, char* argv[])
{
    Camera camera;
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, camera);

    std::vector<std::vector<int>> heights;
    if (argc > 1)
    {
        heights = LoadTerrain(std::string(argv[1]));
    }
    else
    {
        std::cout << "No terrain File";
        std::exit(-1);
    }

    if (!renderer.initialize())
    {
        std::cout << "Could not initialize openGL" << std::endl;
        std::exit(-1);
    }

    SDL_Event eventHandler;
    InputHandler inputHandler;
    std::queue<GameEvent> eventQueue;

    auto cubes = createCubes(renderer, heights);
    float deltaTime = 0.1f;

    while (renderer.windowIsOpen())
    {
        bool keepWindowOpen = inputHandler.processEvents(eventHandler, eventQueue);
        
        auto clockStart = std::chrono::high_resolution_clock::now();
        camera.update(deltaTime);

        renderer.keepWindowOpen(keepWindowOpen);
        renderer.clear();

        for (std::size_t i = 0; i < cubes.size(); ++i)
        {
            for (std::size_t j = 0; j < cubes[i].size(); ++j)
            {
                for (std::size_t k = 0; k < cubes[i][j].size(); ++k)
                {
                    cubes[i][j][k]->update(deltaTime);
                    cubes[i][j][k]->draw();
                }
            }
        }

        renderer.present();


        while (!eventQueue.empty())
        {
            GameEvent nextEvent = eventQueue.front();
            eventQueue.pop();
        
            switch (nextEvent.action)
            {
                case ActionEnum::RAISE:
                    std::cout << "Raise" << std::endl;
                    break;
                case ActionEnum::LOWER:
                    std::cout << "Lower" << std::endl;
                    break;
                case ActionEnum::RESET:
                    std::cout << "Reset" << std::endl;
                    break;
                case ActionEnum::LATER:
                    renderer.advanceLight(deltaTime);
                    std::cout << "LATER" << std::endl;
                    break;
                case ActionEnum::EARLIER:
                    renderer.regressLight(deltaTime);
                    std::cout << "EARLIER" << std::endl;
                    break;
            }
        }
        //SDL_Delay(30);
        auto clockStop = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(clockStop - clockStart).count();
    }

    return 0;
}