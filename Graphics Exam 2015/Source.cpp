#include <iostream>
#include <chrono>

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

void LoadTerrain(const std::string& terrainFilename)
{
    //std::ifstream inputFile(terrainFilename);
}

int main(int argc, char* argv[])
{
    Camera camera;
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, camera);

    SDL_Event eventHandler;
    InputHandler inputHandler;
    std::queue<GameEvent> eventQueue;

    SceneObject object(renderer,
                       "DirectionalFullTexture",
                       "Cube",
                       "Bricks",
                       glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

    SceneObject object2(renderer,
                        "DirectionalFullTexture",
                        "Cube",
                        "Bricks",
                        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                        glm::vec3(0.0f, 0.0f, -10.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(2.0f, 2.0f, 2.0f));

    if (!renderer.initialize())
    {
        std::cout << "Could not initialize openGL" << std::endl;
        std::exit(-1);
    }

    float deltaTime = 0.1f;
    while (renderer.windowIsOpen())
    {
        bool keepWindowOpen = inputHandler.processEvents(eventHandler, eventQueue);

        auto clockStart = std::chrono::high_resolution_clock::now(); 
        camera.update(deltaTime);
        renderer.keepWindowOpen(keepWindowOpen);
        renderer.clear();
        object.draw();
        object.update(deltaTime);
        object2.draw();
        object2.update(deltaTime);
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
            }
        }
        SDL_Delay(30);
        auto clockStop = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(clockStop - clockStart).count();
    }

    return 0;
}