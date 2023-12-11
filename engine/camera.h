#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"
#include "motor.h"

class LIB_API Camera : public Node {
private:


public:
    Camera();

    // Functions to retrieve camera matrices
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    //get inverse matrix
    glm::mat4 getInverseMatrix();

    // Override the get_final_matrix() method
    void get_final_matrix() override;

    // Other camera-related methods...

};

#endif // CAMERA_H
