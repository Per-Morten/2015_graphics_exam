//===========================================================
// File: Camera.h	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Consts.h"

class Camera
{
public:
    Camera() noexcept;
    ~Camera() noexcept;

    void update(float deltaTime) noexcept;
    const glm::mat4& getViewMatrix() const noexcept;
    const glm::vec3& getPosition() const noexcept;

    void rotate(const glm::vec3& rotationVector) noexcept;
    void strafeLeft(float deltaTime) noexcept;
    void strafeRight(float deltaTime) noexcept;
    void moveForward(float deltaTime) noexcept;
    void moveBack(float deltaTime) noexcept;
    void moveUp(float deltaTime) noexcept;
    void moveDown(float deltaTime) noexcept;

    void rotateCamera(const glm::vec2& newMousePosition) noexcept;

    static constexpr float maxViewDistance = 10000.0f;
    static constexpr float minViewDistance = 0.1f;
    static constexpr float mouseDownScale = 1.0f / 100.0f;
    static constexpr float cameraSensitivity = 100.0f;
    const glm::vec2 mouseStartPos = { Consts::SCREEN_WIDTH / (cameraSensitivity * 2), Consts::SCREEN_HEIGHT / (cameraSensitivity * 2) };

    const glm::vec3 startPosition = { 0.0f, 200.0f, -300.0f };
    const glm::vec3 upDirection = { 0.0f, 1.0f, 0.0f };
    const glm::vec3 startFocusPoint = { 0.0f,0.0f,0.0f };
    const float movementSpeed = { 100.0f };

private:
    glm::vec3 _position{ startPosition };
    glm::mat4 _viewMatrix{};
    glm::vec3 _viewDirection{ 0.0f, 0.0f, 1.0f };
};