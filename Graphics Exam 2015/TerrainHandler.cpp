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
    for (auto& object : _drawableSceneObjects)
    {
        object->update(deltaTime);
        object->draw();
    }
}

void TerrainHandler::addCube(std::size_t xIndex, std::size_t zIndex) noexcept
{
    auto size = _sceneObjects[xIndex][zIndex].size();
    glm::vec3 newPosition;
    if (size > 0)
    {
        newPosition = _sceneObjects[xIndex][zIndex][size - 1]->getPosition();
        newPosition.y += SceneObject::cubeSize;
    }
    else
    {
        newPosition = { xIndex * SceneObject::cubeSize, 0.0f, zIndex * SceneObject::cubeSize };
    }
    _sceneObjects[xIndex][zIndex].push_back(new SceneObject(_renderer,
                                                            "DirectionalFullTexture",
                                                            "Cube",
                                                            "Bricks",
                                                            0,
                                                            newPosition));
    applyCorrectTextures();
    hideUndrawableTerrain();
    createDrawableSceneList();
}

void TerrainHandler::deleteCube(std::size_t xIndex, std::size_t zIndex) noexcept
{
    std::size_t size = _sceneObjects[xIndex][zIndex].size();
    if (size > 0)
    {
        delete _sceneObjects[xIndex][zIndex][size - 1];

        _sceneObjects[xIndex][zIndex].pop_back();
        applyCorrectTextures();
        hideUndrawableTerrain();
        createDrawableSceneList();
    }
}

void TerrainHandler::createTerrain(const HeightMap& heightMap) noexcept
{
    _sceneObjects.resize(heightMap.size());
    for (std::size_t i = 0; i < heightMap.size(); ++i)
    {
        _sceneObjects[i].resize(heightMap[i].size());
        for (std::size_t j = 0; j < heightMap[i].size(); ++j)
        {
            for (int k = 0; k < heightMap[i][j]; ++k)
            {
                SceneObject* object = new SceneObject(_renderer,
                                                      "DirectionalFullTexture",
                                                      "Cube",
                                                      "Bricks",
                                                      1,
                                                      glm::vec3(i * SceneObject::cubeSize, k * SceneObject::cubeSize, j * SceneObject::cubeSize),
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                                      glm::vec3(0.0f, 0.0f, 0.0f));
                _sceneObjects[i][j].push_back(object);
            }
        }
    }
    applyCorrectTextures();
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
    for (std::size_t i = 0; i < _sceneObjects.size(); ++i)
    {
        for (std::size_t j = 0; j < _sceneObjects[i].size(); ++j)
        {
            for (std::size_t k = 0; k < _sceneObjects[i][j].size(); ++k)
            {
                temp.push_back(_sceneObjects[i][j][k]);
            }
        }
    }

    auto tempEnd = std::partition(temp.begin(), temp.end(), [](auto& object) { return object->isVisible(); });

    // Copy into the list of drawable elements
    _drawableSceneObjects.clear();
    std::copy(temp.begin(), tempEnd, std::back_inserter(_drawableSceneObjects));

    // Sort it based on the texture offset so we don't have to send that uniform so often
    std::sort(_drawableSceneObjects.begin(), _drawableSceneObjects.end(), [](auto& a, auto& b) { return (a->getTextureOffset().x < b->getTextureOffset().x); });
}

void TerrainHandler::applyCorrectTextures() noexcept
{
    for (std::size_t i = 0; i < _sceneObjects.size(); ++i)
    {
        for (std::size_t j = 0; j < _sceneObjects[i].size(); ++j)
        {
            for (std::size_t k = 0; k < _sceneObjects[i][j].size(); ++k)
            {
                glm::vec2 textureOffset;
                if (k < shallowWaterLevel)
                {
                    textureOffset = SceneObject::deepWaterOffset;
                }
                else if (k < dirtLevel)
                {
                    textureOffset = SceneObject::shallowWaterOffset;
                }
                else if (k < grassLevel)
                {
                    textureOffset = SceneObject::dirtOffset;
                }
                else if (k < snowLevel)
                {
                    textureOffset = SceneObject::grassOffset;
                }
                else
                {
                    textureOffset = SceneObject::snowOffset;
                }

                //make sure borders of the map get the dirt texture
                if ((i == 0 || i == _sceneObjects.size() - 1 ||
                     j == 0 || j == _sceneObjects[i].size() - 1) &&
                    k < _sceneObjects[i][j].size() - 1 && k > dirtLevel && (k <= snowLevel))
                {
                    textureOffset = SceneObject::dirtOffset;
                }
                if (k < _sceneObjects[i][j].size() - 1 && k > dirtLevel && (k <= snowLevel))
                {
                    textureOffset = SceneObject::dirtOffset;
                }

                _sceneObjects[i][j][k]->setTextureOffset(textureOffset);
            }
        }
    }
}

