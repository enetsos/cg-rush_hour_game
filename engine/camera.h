#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "motor.h"
#include "node.h"


class LIB_API Camera : public Node{
public:
    Camera();

    void setLookAt(const glm::vec3& lookAt);
    void setUpVector(const glm::vec3& upVector);
    void setProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 upVector;
    glm::mat4 projectionMatrix;
};

#endif // CAMERA_H
