#include "TerrainHandler.h"
#include <algorithm>
#include <iostream>


TerrainHandler::TerrainHandler(Renderer& renderer, const HeightMap& heightMap) noexcept
    :_renderer(renderer)
{
    createTerrain(heightMap);
    hideUndrawableTerrain();
    createDrawableSceneList();
}

TerrainHandler::~TerrainHandler() noexcept
{
    for (std::size_t i = 0; i < _sceneObjects.size(); ++i)
    {
        for (std::size_t j = 0; j < _sceneObjects[i].size(); ++j)
        {
            for (std::size_t k = 0; k < _sceneObjects[i][j].size(); ++k)
            {
                delete _sceneObjects[i][j][k];
            }
        }
    }
}

void TerrainHandler::update(float deltaTime) noexcept
{
    //int counter = 0;
    //for (std::size_t i = 0; i < _drawableSceneObjects.size(); ++i)
    //{
    //    ++counter;
    //    _drawableSceneObjects[i]->update(deltaTime);
    //    _drawableSceneObjects[i]->draw();
    //}
    //std::cout << "Per-Morten:" << counter << std::endl;

    for (auto& object : _drawableSceneObjects)
    {
        object->update(deltaTime);
        object->draw();
    }
}

void TerrainHandler::createTerrain(const HeightMap& heightMap) noexcept
{

    const glm::vec2 dirtOffset{ 0.0f, 0.0f };
    const glm::vec2 grassOffset{ 0.25f, 0.0f };
    const glm::vec2 snowOffset{ 0.50f, 0.0f };
    const glm::vec2 waterOffset{ 0.75f, 0.0f };

    _sceneObjects.resize(heightMap.size());
    for (std::size_t i = 0; i < heightMap.size(); ++i)
    {
        _sceneObjects[i].resize(heightMap[i].size());

        for (std::size_t j = 0; j < heightMap[i].size(); ++j)
        {
            for (int k = 0; k < heightMap[i][j]; ++k)
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
                else
                {
                    textureOffset = snowOffset;
                }
                SceneObject* object = new SceneObject(_renderer,
                                                      "DirectionalFullTexture",
                                                      "Cube",
                                                      "Bricks",
                                                      glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                                      glm::vec3(i * 10, k * 10.0f, j * 10),
                                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      textureOffset);
                _sceneObjects[i][j].push_back(object);
            }
        }
    }
}

void TerrainHandler::hideUndrawableTerrain() noexcept
{
    constexpr std::size_t maxSizeT = std::numeric_limits<std::size_t>::max();

    for (std::size_t i = 0; i < _sceneObjects.size(); ++i)
    {
        for (std::size_t j = 0; j < _sceneObjects[i].size(); ++j)
        {
            for (std::size_t k = _sceneObjects[i][j].size() - 1; k != maxSizeT; --k)
            {
                // Draw and update the cubes which should be visible
                bool hidden = false;
                if (i != 0 && i != _sceneObjects.size() - 1 &&
                    j != 0 && j != _sceneObjects[i].size() - 1 &&
                    k != 0 && k != _sceneObjects[i][j].size() - 1)
                {
                    hidden = true;
                    hidden = hidden && (k < _sceneObjects[i + 1][j + 0].size()); // Right
                    hidden = hidden && (k < _sceneObjects[i + 0][j + 1].size()); // Up
                    hidden = hidden && (k < _sceneObjects[i - 1][j + 0].size()); // Left
                    hidden = hidden && (k < _sceneObjects[i + 0][j - 1].size()); // Down
                }
                if (!hidden)
                {
                    _sceneObjects[i][j][k]->setVisible(true);
                }
            }
        }
    }
}
void TerrainHandler::createDrawableSceneList() noexcept
{
    
    SceneObjectList temp;
    std::size_t counter = 0;
    for (std::size_t i = 0; i < _sceneObjects.size(); ++i)
    {
        for (std::size_t j = 0; j < _sceneObjects[i].size(); ++j)
        {
            for (std::size_t k = 0; k < _sceneObjects[i][j].size(); ++k)
            {
                ++counter;
                temp.push_back(_sceneObjects[i][j][k]);
            }
        }
    }

    auto tempEnd = std::partition(temp.begin(), temp.end(), [](auto& object){return object->isVisible();});
    
    // Copy into the list of drawable elements
    std::copy(temp.begin(), tempEnd,std::back_inserter(_drawableSceneObjects));
    std::sort(_drawableSceneObjects.begin(), _drawableSceneObjects.end(), [](auto& a, auto& b) {return (a->getTextureOffset().x < b->getTextureOffset().x);});

    int timesSwitched = 0;
    for (std::size_t i = 1; i < _drawableSceneObjects.size(); ++i)
    {
        if (_drawableSceneObjects[i]->getTextureOffset().x != _drawableSceneObjects[i - 1]->getTextureOffset().x)
        {
            timesSwitched++;
        }
    }
    std::cout << _drawableSceneObjects.size() << std::endl;
    std::cout << "times switched: " << timesSwitched << std::endl;
}

