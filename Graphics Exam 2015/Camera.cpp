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
    //rotate(glm::vec3({ 0.0f, 1.0f, 0.0f }) * deltaTime);
    static float counter;
    //counter -= deltaTime;
    //_focusPoint.z -= counter;
    //_position.z += deltaTime * 15;
    //_viewMatrix = glm::lookAt(_position, _focusPoint, { 0.0f, 1.0f, 0.0f });
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return _viewMatrix;
}

void Camera::rotate(const glm::vec3& rotationVector) noexcept
{
    _viewMatrix = glm::rotate(_viewMatrix, glm::length(rotationVector), rotationVector);
}

void Camera::moveCamera(const glm::vec3& movement) noexcept
{
    _position = _position + movement;
}

void Camera::updateMovableCamera() noexcept
{
    _viewMatrix = glm::lookAt(_position, _position + _viewDirection, upDirection);
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

