#pragma once
#include <string>

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "Renderer.h"

class SceneObject
{
public:
    static constexpr float cubeSize = 10.0f;
    static const glm::vec2 deepWaterOffset;
    static const glm::vec2 shallowWaterOffset;
    static const glm::vec2 dirtOffset;
    static const glm::vec2 grassOffset;
    static const glm::vec2 snowOffset;


    SceneObject() = delete;
    SceneObject(Renderer& renderer,
                const std::string& shaderName,
                const std::string& meshName,
                const std::string& textureName,
                GLuint textureIndex,
                const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f),
                const glm::vec4& color = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f),
                const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                Renderer::FacingDirection facingDirection = Renderer::FacingDirection::BACK) noexcept;
    
    ~SceneObject() noexcept;

    void update(float deltaTime) noexcept;
    void draw() noexcept;
    

    void setColor(const glm::vec4& color) noexcept;
    void setPosition(const glm::vec3& position) noexcept;
    void setRotation(const glm::vec3& rotation) noexcept;
    void setScale(const glm::vec3& scale) noexcept;
    void setTextureOffset(const glm::vec2& textureOffset) noexcept;
    void setVisible(bool isVisible) noexcept;
   
    const glm::vec4& getColor() const noexcept;
    const glm::vec3& getPosition() const noexcept;
    const glm::vec3& getRotation() const noexcept;
    const glm::vec3& getScale() const noexcept;
    const glm::vec2& getTextureOffset() const noexcept;
    bool isVisible() const noexcept;

private:
    Renderer& _renderer;
    std::string _shaderName{};
    std::string _meshName{};
    std::string _textureName{};

    glm::vec4 _color{};
    glm::vec3 _position{};
    glm::vec3 _rotation{};
    glm::vec3 _scale{};
    glm::mat4 _modelMatrix{ 1 };
    glm::vec2 _textureOffset{};
    Renderer::FacingDirection _facingDirection{};
    bool _isVisible{false};
    
    // For indexed texture
    GLuint _textureIndex{0};
};