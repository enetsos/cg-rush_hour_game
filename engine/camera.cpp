#include "camera.h"

Camera::Camera() : position(glm::vec3(0.0f)) {}

void Camera::set_position(const glm::vec3& _position) {
    position = _position;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}
