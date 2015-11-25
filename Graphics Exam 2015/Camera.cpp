#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() noexcept
    : _viewMatrix(glm::lookAt(_position, _focusPoint, upDirection))
{
}

Camera::~Camera() noexcept
{
}

void Camera::update(float deltaTime) noexcept
{
    _viewMatrix = glm::lookAt(_position, _position + _viewDirection, upDirection);
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return _viewMatrix;
}

void Camera::rotate(const glm::vec3& rotationVector) noexcept
{
    _viewMatrix = glm::rotate(_viewMatrix, glm::length(rotationVector), rotationVector);
}

void Camera::strafeLeft(float deltaTime) noexcept
{
    glm::vec3 directionToStrafe = glm::cross(_viewDirection, upDirection);
    _position -= directionToStrafe * movementSpeed * deltaTime;
}

void Camera::strafeRight(float deltaTime) noexcept
{
    glm::vec3 directionToStrafe = glm::cross(_viewDirection, upDirection);
    _position += directionToStrafe * movementSpeed * deltaTime;
}

void Camera::moveForward(float deltaTime) noexcept
{
    _position += _viewDirection * movementSpeed * deltaTime;
}

void Camera::moveBack(float deltaTime) noexcept
{
    _position -= _viewDirection * movementSpeed * deltaTime;
}

void Camera::moveUp(float deltaTime) noexcept
{
    _position += upDirection * movementSpeed * deltaTime;
}

void Camera::moveDown(float deltaTime) noexcept
{
    _position -= upDirection * movementSpeed * deltaTime;
}

void Camera::rotateCamera(const glm::vec2& newMousePosition) noexcept
{
    static glm::vec2 oldMousePosition;
    glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
    _viewDirection = glm::mat3(glm::rotate(-mouseDelta.x, upDirection)) * _viewDirection;

    // Find a vector to rotate around, think of rotating around Z in 2D Space
    glm::vec3 toRotateAround = glm::cross(_viewDirection, upDirection);
    _viewDirection = glm::mat3(glm::rotate(-mouseDelta.y, toRotateAround)) * _viewDirection;

    oldMousePosition = newMousePosition;

}

