#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
    Camera() noexcept;
    ~Camera() noexcept;

    void update(float deltaTime) noexcept;
    const glm::mat4& getViewMatrix() const noexcept;

    void rotate(const glm::vec3& rotationVector) noexcept;
    
    static constexpr float maxViewDistance = 100.0f;
    static constexpr float minViewDistance = 0.1f;
    const glm::vec3 startPosition = { 0.0f, 0.0f, 30.0f };
    const glm::vec3 startFocus = { 0.0f, 0.0f, 0.0f };

private:
    glm::vec3 _position{ startPosition };
    glm::vec3 _focusPoint{ startFocus };
    glm::mat4 _viewMatrix{};
};