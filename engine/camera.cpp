#include "camera.h"

// Constructor
Camera::Camera() : isPerspective(true) {
    // Default perspective setup
    setPerspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

// Destructor
Camera::~Camera() {
    // Cleanup code
}

// Set perspective projection
void Camera::setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    isPerspective = true;
}

// Set orthographic projection
void Camera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    isPerspective = false;
}

// Get the projection matrix
const glm::mat4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

// Other implementation details...
