#include "mesh.h"
#include <GL/freeglut.h>

// Constructor
Mesh::Mesh() {
    // Initialization code for older OpenGL
}

// Destructor
Mesh::~Mesh() {
    // Cleanup code for older OpenGL
}

// Set vertices (for older OpenGL, this might store vertices in a custom format)
void Mesh::setVertices(const std::vector<Vertex>& vertices) {
    this->vertices = vertices;
    // Process vertices as needed for older OpenGL rendering
}

// Set indices (might not be used in older OpenGL)
void Mesh::setIndices(const std::vector<unsigned int>& indices) {
    this->indices = indices;
    // Process indices as needed for older OpenGL rendering
}

// Render the mesh using older OpenGL methods
void Mesh::render() {
    glBegin(GL_TRIANGLES);
    for (const auto& vertex : vertices) {
        glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
        // Similarly for normals and texture coordinates, if used
    }
    glEnd();
}
