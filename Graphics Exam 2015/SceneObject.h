#pragma once
#include <string>

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "Renderer.h"

class SceneObject
{
public:
    static constexpr float cubeSize = 10.0f;
    static constexpr GLuint dirtTexture = 0;
    static constexpr GLuint grassTexture = 1;
    static constexpr GLuint snowTexture = 2;
    static constexpr GLuint shallowWaterTexture = 3;
    static constexpr GLuint oneNumberTexture = 4;
    static constexpr GLuint twoNumberTexture = 5;
    static constexpr GLuint threeNumberTexture = 6;
    static constexpr GLuint fourNumberTexture = 7;
    static constexpr GLuint fiveNumberTexture = 8;
    static constexpr GLuint sixNumberTexture = 9;
    static constexpr GLuint grass2Texture = 10;
    static constexpr GLuint snow2Texture = 11;
    static constexpr GLuint deepWaterTexture = 12;
    static constexpr GLuint desertTexture = 13;
    static constexpr GLuint dirt2Texture = 14;
    static constexpr GLuint rockTexture = 15;


    SceneObject() = delete;
    SceneObject(Renderer& renderer,
                const std::string& shaderName,
                const std::string& meshName,
                const std::string& textureName,
                GLuint textureIndex,
                const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f),
                const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                Renderer::FacingDirection facingDirection = Renderer::FacingDirection::BACK) noexcept;

    ~SceneObject() noexcept;

    void update(float deltaTime) noexcept;
    void draw() noexcept;

    void setTextureIndex(GLuint textureIndex) noexcept;
    void setColor(const glm::vec4& color) noexcept;
    void setPosition(const glm::vec3& position) noexcept;
    void setRotation(const glm::vec3& rotation) noexcept;
    void setScale(const glm::vec3& scale) noexcept;
    void setVisible(bool isVisible) noexcept;
    void setUpdated() noexcept;

    const glm::vec4& getColor() const noexcept;
    const glm::vec3& getPosition() const noexcept;
    const glm::vec3& getRotation() const noexcept;
    const glm::vec3& getScale() const noexcept;
    GLuint getTextureIndex() const noexcept;
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
    Renderer::FacingDirection _facingDirection{};
    bool _isVisible{ false };
    bool _hasBeenUpdated{ true };

    // For indexed texture
    GLuint _textureIndex{ 0 };
};