#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "motor.h"
#include "node.h"

class LIB_API Camera : public Node {
public:
    // Constructors and Destructor
    Camera();
    virtual ~Camera();

    // Camera setup methods
    void setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    // Getters for the projection matrix
    const glm::mat4& getProjectionMatrix() const;

private:
    glm::mat4 projectionMatrix;
    bool isPerspective;
};
#endif // CAMERA_H
