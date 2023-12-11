#include "mesh.h"
#include <GL/freeglut.h>


Mesh::Mesh(string name) : Node(name) {
    // Initialize material or set it to null, depending on your requirements
    // material_ = nullptr;  // Uncomment if using materials
}

Mesh::~Mesh() {
    // Release any allocated resources or cleanup, if needed
}

void Mesh::loadGemetry(const char* path) {
    // Placeholder implementation for loading geometry from a file
    // You would need to replace this with your actual implementation
    std::cout << "Loading geometry from file: " << path << std::endl;
    // Implement your file loading logic here
}

bool LIB_API Mesh::render(glm::mat4 m) {
    m += glm::vec4{ 0.0f };
    displayCube(20.0f);
    return true;
}

void LIB_API Mesh::displayCube(float length) {

    float size = length / 2.0f;

    // Back:
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    // Front:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glEnd();

    // Left:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, -size, size);
    glEnd();

    // Right:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glEnd();

    // Bottom:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glEnd();

    // Top:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
    //material->render(glm::mat4{ 0.0f });
}
