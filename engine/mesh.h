#pragma once
#ifndef MESH_H
#define MESH_H

#pragma once
#include "motor.h"
#include "node.h"



// Vertex structure
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class LIB_API Mesh : public Node {
public:
    // Constructors and Destructor
    Mesh();
    virtual ~Mesh();

    // Mesh setup methods
    void setVertices(const std::vector<Vertex>& vertices);
    void setIndices(const std::vector<unsigned int>& indices);

    // Rendering method
    void render();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    // OpenGL identifiers for vertex array and buffer objects
    unsigned int VAO, VBO, EBO;
};

#endif // MESH_H
