#include "camera.h"

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 3.0f)),
      lookAt(glm::vec3(0.0f, 0.0f, 0.0f)),
      upVector(glm::vec3(0.0f, 1.0f, 0.0f)) {
  setProjection(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::setLookAt(const glm::vec3 &look) { lookAt = look; }

void Camera::setUpVector(const glm::vec3 &up) { upVector = up; }

void Camera::setProjection(float fov, float aspectRatio, float nearPlane,
                           float farPlane) {
  projectionMatrix =
      glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, lookAt, upVector);
}

glm::mat4 Camera::getProjectionMatrix() const { return projectionMatrix; }
