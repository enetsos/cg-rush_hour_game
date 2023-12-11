#pragma once
#pragma once
#ifndef MESH_H
#define MESH_H

#include "node.h"
#include "motor.h"
#include "material.h"
#include <vector>
//#include "material.h"  // Assuming there is a Material class

class LIB_API Mesh : public Node {
public:
    // Constructor
    Mesh(string _name, Material* _material) : Node(_name), material(_material) {};

    // Destructor
    ~Mesh();

    // Set mesh data (for simplicity, assume a cube for now)
    void displayCube(float length);

    void loadGemetry(const char* path);

    // Render the mesh using OpenGL
    bool render(glm::mat4 modelMatrix) override;

private:
    std::vector<glm::vec3> vertices_;

    // Reference to the material used by the mesh
    Material* material;
};

#endif // MESH_H
