#pragma once

#include "motor.h"

class Camera {
public:
    Camera();
    void set_position(const glm::vec3& position);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

private:
    glm::vec3 position;
};
