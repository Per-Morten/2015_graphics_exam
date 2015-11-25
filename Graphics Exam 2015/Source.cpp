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

// Force external GPU
// As my PC Sometimes decides 
extern "C"
{
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// Defines etc for easier reads.
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
std::string windowName = "Graphics Exam 2015 - Per-Morten Straume";

namespace GameObject
{
    using SceneObjectList = std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>>;
}

std::vector<std::vector<int>> generateTerrain()
{
    std::random_device randomizer;
    std::default_random_engine engine(randomizer());
    std::uniform_int_distribution<std::size_t> distribution(1,100);

    int kvadraticSize = distribution(engine);
    std::vector<std::vector<int>> height;
    height.resize(kvadraticSize);
    
    for (std::size_t i = 0; i < height.size(); ++i)
    {
        height[i].resize(kvadraticSize);
        for (std::size_t j = 0; j < height[i].size(); ++j)
        {
            height[i][j] = distribution(engine);
        }
    }
    return height;
}

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

GameObject::SceneObjectList createCubes(Renderer& renderer, std::vector<std::vector<int>> heights)
{
    std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>> objects;

    const glm::vec2 dirtOffset{ 0.0f, 0.0f };
    const glm::vec2 grassOffset{ 0.25f, 0.0f };
    const glm::vec2 snowOffset{ 0.50f, 0.0f };
    const glm::vec2 waterOffset{ 0.75f, 0.0f };

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
                    textureOffset = waterOffset;
                }
                else if (k < 3)
                {
                    textureOffset = dirtOffset;
                }
                else if (k < 18)
                {
                    textureOffset = grassOffset;
                }
                else if (k < 21)
                {
                    textureOffset = snowOffset;
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

void deleteCubes(GameObject::SceneObjectList& toBeDeleted)
{
    for (std::size_t i = 0; i < toBeDeleted.size(); ++i)
    {
        for (std::size_t j = 0; j < toBeDeleted[i].size(); ++j)
        {
            for (std::size_t k = 0; k < toBeDeleted[i][j].size(); ++k)
            {
                delete toBeDeleted[i][j][k];
            }
        }
    }
}
// In development
void createCube(Camera& camera, GameObject::SceneObjectList& objects) noexcept
{
    glm::vec3 position = camera.getPosition();
    glm::vec3 indexPos = { (position.x / 10) - 5,(position.x / 10) - 5, position.y };

    if (indexPos.x >= 0 && indexPos.x < objects.size())
    {
        if (indexPos.y < objects[indexPos.x].size())
        {
            static int counter;
            counter++;
            std::cout << indexPos.x << "\t" << indexPos.y << std::endl;
        }
    }
}

void handleInput(std::queue<GameEvent>& eventQueue,
                 Renderer& renderer,
                 Camera& camera,
                 float deltaTime,
                 glm::vec2& mousePosition,
                 GameObject::SceneObjectList& objects)
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
                    camera.rotateCamera(mousePosition / 100.0f);
                }
                break;

            case ActionEnum::ENABLEMOVEMENT:
                enableMovement = !enableMovement;
                break;

            case ActionEnum::CREATE:
                createCube(camera, objects);
                break;

            case ActionEnum::DESTROY:
                std::cout << "Destroy" << std::endl;
                break;

            case ActionEnum::GENERATE:
                deleteCubes(objects);
                objects = createCubes(renderer, generateTerrain());
                break;

        }
    }
}

void drawVisibleObjects(const GameObject::SceneObjectList& objects, float deltaTime) noexcept
{
    constexpr std::size_t maxSizeT = std::numeric_limits<std::size_t>::max();

    for (std::size_t i = 0; i < objects.size(); ++i)
    {
        for (std::size_t j = 0; j < objects[i].size(); ++j)
        {
            for (std::size_t k = objects[i][j].size() - 1; k != maxSizeT; --k)
            {
                // Draw and update the cubes which should be visible
                bool hidden = false;
                if (i != 0 && i != objects.size() - 1 &&
                    j != 0 && j != objects[i].size() - 1 &&
                    k != 0 && k != objects[i][j].size() - 1)
                {
                    hidden = true;
                    hidden = hidden && (k < objects[i + 1][j + 0].size()); // Right
                    hidden = hidden && (k < objects[i + 0][j + 1].size()); // Up
                    hidden = hidden && (k < objects[i - 1][j + 0].size()); // Left
                    hidden = hidden && (k < objects[i + 0][j - 1].size()); // Down
                }
                if (!hidden)
                {
                    objects[i][j][k]->update(deltaTime);
                    objects[i][j][k]->draw();
                }
            }
        }
    }
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
    glm::vec2 mousePosition;


    auto cubes = createCubes(renderer, heights);
    float deltaTime = 0.1f;

    while (renderer.windowIsOpen())
    {
        bool keepWindowOpen = inputHandler.processEvents(eventHandler, eventQueue, mousePosition);

        auto clockStart = std::chrono::high_resolution_clock::now();
        camera.update(deltaTime);
        renderer.keepWindowOpen(keepWindowOpen);
        renderer.clear();

        drawVisibleObjects(cubes, deltaTime);
        renderer.present();
        handleInput(eventQueue, renderer, camera, deltaTime, mousePosition, cubes);

        auto clockStop = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(clockStop - clockStart).count();
        printf("%f\n", 1/deltaTime);
    }

    return 0;
}