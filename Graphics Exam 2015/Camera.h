#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
class Camera
{
public:
    Camera() noexcept;
    ~Camera() noexcept;

    void update(float deltaTime) noexcept;
    const glm::mat4& getViewMatrix() const noexcept;

    void rotate(const glm::vec3& rotationVector) noexcept;
    void moveCamera(const glm::vec3& movement) noexcept;
    void updateMovableCamera() noexcept;

    void rotateCamera(const glm::vec2& newMousePosition) noexcept;

    static constexpr float maxViewDistance = 1000.0f;
    static constexpr float minViewDistance = 0.1f;
    const glm::vec3 startPosition = { 0.0f, 300.0f, -500.0f };
    const glm::vec3 startFocus = { 0.0f, 0.0f, 0.0f };
    const glm::vec3 upDirection = { 0.0f, 1.0f, 0.0f };
private:
    glm::vec3 _position{ startPosition };
    glm::vec3 _focusPoint{ startFocus };
    glm::mat4 _viewMatrix{};
    glm::vec3 _viewDirection{ 0.0f, 0.0f, 1.0f };
};