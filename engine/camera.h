#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"
#include "motor.h"

class LIB_API Camera : public Node {
private:

public:
    Camera(glm::mat4 _matrix, bool _isOrtho);

    //get orthographic matrix
    glm::mat4 getOrthographicMatrix();

    //get projection matrix
    glm::mat4 getProjectionMatrix();

    //get inverse matrix
    glm::mat4 getInverseMatrix();


};

#endif // CAMERA_H
