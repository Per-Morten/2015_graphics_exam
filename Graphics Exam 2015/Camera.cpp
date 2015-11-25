#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() noexcept
    : _viewMatrix(glm::lookAt(_position, _focusPoint, { 0.0f, 1.0f, 0.0f }))
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
    _viewMatrix = glm::lookAt(_position, _position + _viewDirection, glm::vec3{ 0.0f, 1.0f, 0.0f });
}

