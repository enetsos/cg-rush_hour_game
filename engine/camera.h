#pragma once
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"
#include "motor.h"

class LIB_API Camera : public Node {
private:

public:
    void setProjectionMatrix(glm::mat4 m);
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getInverseMatrix() const;
};

#endif // CAMERA_H

