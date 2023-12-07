#pragma once
#ifndef MESH_H
#define MESH_H

#include "node.h"
#include "material.h"
#include <vector>
#include "motor.h"

class LIB_API Mesh : public Node {
private:
    std::vector<glm::vec3> vertexes;
    //glm::vec3 textureCoordinates;
    Material* material;

public:
    Mesh(string _name, Material* _material) : Node(_name), material{ _material } {};
    virtual ~Mesh() {
        delete material;
    }
    void loadGeometry(const char* filePath);
    void displayCube(float length);
    bool render(glm::mat4 m) override;

};

#endif // MESH_H
