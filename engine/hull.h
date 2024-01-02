#pragma once
#include "motor.h"

struct Hull {
    glm::vec3 centroid;
    std::vector<glm::vec3> vertices;
    unsigned int faces[3]; // Assuming each face is represented by 3 indices for triangles

    // Constructors and other utility methods as needed...
};
