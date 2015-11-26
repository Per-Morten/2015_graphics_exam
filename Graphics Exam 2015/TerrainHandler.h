#pragma once
#include "SceneObject.h"
#include "Renderer.h"
#include <vector>


class TerrainHandler
{
public:
    using SceneObject3DList = std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>>;
    using SceneObjectList = std::vector<SceneObject*>;
    using HeightMap = std::vector<std::vector<int>>;

    TerrainHandler(Renderer& renderer,const HeightMap& heightMap) noexcept;
    ~TerrainHandler() noexcept;

    void update(float deltaTime) noexcept;

private:
    void createTerrain(const HeightMap& heightMap) noexcept;
    void hideUndrawableTerrain() noexcept;
    void createDrawableSceneList() noexcept;

    Renderer& _renderer;
    SceneObject3DList _sceneObjects{};
    SceneObjectList _drawableSceneObjects{};
    
    SceneObjectList::iterator _drawableSceneObjectsEnd{};


};