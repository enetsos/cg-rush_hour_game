#pragma once
#include "motor.h"


struct LOD {
    unsigned int numVertices;
    unsigned int numFaces;
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> normals;
    std::vector<unsigned int> textureCoords;
    std::vector<unsigned int> tangents;
    unsigned int faces [3]; // Assuming face is represented by 3 indices for triangles

    // Constructors and other utility methods as needed...
};
