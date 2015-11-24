#pragma once
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

class Mesh
{
public:
    using IndexBufferObject = GLuint;
    using VertexBufferObject = GLuint;
    using VertexAttributeObject = GLuint;

    Mesh() = delete;
    Mesh(const std::vector<glm::vec3>& vertexPositions,
         const std::vector<glm::vec3>& vertexNormals,
         const std::vector<glm::vec2>& textureCoordinates,
         const std::vector<GLuint>& IBO) noexcept;
    ~Mesh() noexcept;

    void draw() noexcept;
private:
    IndexBufferObject _indexBufferObject{};
    VertexAttributeObject _vertexAttributeObject{};
    GLuint _drawCount{};
};