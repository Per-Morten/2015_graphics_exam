#include "SceneObject.h"

#include <glm\gtx\transform.hpp>

SceneObject::SceneObject(Renderer& renderer,
                         const std::string& shaderName,
                         const std::string& meshName,
                         const std::string& textureName,
                         GLuint textureIndex,
                         const glm::vec3& position,
                         const glm::vec3& scale,
                         const glm::vec4& color,
                         const glm::vec3& rotation,
                         Renderer::FacingDirection facingDirection) noexcept
    : _renderer(renderer)
    , _shaderName(shaderName)
    , _meshName(meshName)
    , _textureName(textureName)
    , _textureIndex(textureIndex)
    , _position(position)
    , _scale(scale)
    , _color(color)
    , _rotation(rotation)
    , _facingDirection(facingDirection)
{
}

SceneObject::~SceneObject() noexcept
{
}

void SceneObject::update(float deltaTime) noexcept
{
    if (_hasBeenUpdated)
    {
        glm::mat4 positionMatrix = glm::translate(_position);

        glm::mat4 rotMatrixX = glm::rotate(_rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotMatrixY = glm::rotate(_rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotMatrixZ = glm::rotate(_rotation.z, glm::vec3(0, 0, 1));
        glm::mat4 rotationMatrix = rotMatrixZ * rotMatrixY * rotMatrixX;

        glm::mat4 scaleMatrix = glm::scale(_scale);

        _modelMatrix = positionMatrix * rotationMatrix * scaleMatrix;
        _hasBeenUpdated = false;
    }
}

void SceneObject::draw() noexcept
{

    _renderer.render(_shaderName, _meshName, _textureName, _modelMatrix, _color, _textureIndex, _facingDirection);

}

void SceneObject::setTextureIndex(GLuint textureIndex) noexcept
{
    _textureIndex = textureIndex;
}

void SceneObject::setColor(const glm::vec4& color) noexcept
{
    _color = color;
}

void SceneObject::setPosition(const glm::vec3& position) noexcept
{
    _position = position;
}

void SceneObject::setRotation(const glm::vec3& rotation) noexcept
{
    _rotation = rotation;
}

void SceneObject::setScale(const glm::vec3& scale) noexcept
{
    _scale = scale;
}


void SceneObject::setVisible(bool isVisible) noexcept
{
    _isVisible = isVisible;
}

void SceneObject::setTexture(const std::string& textureName) noexcept
{
    _textureName = textureName;
}

void SceneObject::setUpdated() noexcept
{
    _hasBeenUpdated = true;
}

const glm::vec4& SceneObject::getColor() const noexcept
{
    return _color;
}

const glm::vec3& SceneObject::getPosition() const noexcept
{
    return _position;
}

const glm::vec3& SceneObject::getRotation() const noexcept
{
    return _rotation;
}

const glm::vec3& SceneObject::getScale() const noexcept
{
    return _scale;
}

GLuint SceneObject::getTextureIndex() const noexcept
{
    return _textureIndex;
}

bool SceneObject::isVisible() const noexcept
{
    return _isVisible;
}
