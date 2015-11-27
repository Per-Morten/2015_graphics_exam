#pragma once
#include <vector>

#include "SceneObject.h"
#include "Renderer.h"


class TerrainHandler
{
public:
    using SceneObjectList = std::vector<SceneObject*>;
    using SceneObject3DList = std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>>;
    using HeightMap = std::vector<std::vector<int>>;

    static constexpr int shallowWaterLevel = 1;
    static constexpr int dirtLevel = 2;
    static constexpr int grassLevel = 3;
    static constexpr int snowLevel = 17;

    TerrainHandler(Renderer& renderer,const HeightMap& heightMap) noexcept;
    ~TerrainHandler() noexcept;

    void update(float deltaTime) noexcept;
    void addCube(std::size_t xIndex, std::size_t zIndex) noexcept;
    void deleteCube(std::size_t xIndex, std::size_t zIndex) noexcept;

    void switchToNextTextureSet() noexcept;
private:
    void createTerrain(const HeightMap& heightMap) noexcept;
    void hideUndrawableTerrain() noexcept;
    void createDrawableSceneList() noexcept;
    void applyCorrectTextures() noexcept;

    Renderer& _renderer;
    SceneObject3DList _sceneObjects{};
    SceneObjectList _drawableSceneObjects{};

    GLuint _baseTexture{};
};