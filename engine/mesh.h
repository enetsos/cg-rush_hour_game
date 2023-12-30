#pragma once
#ifndef MESH_H
#define MESH_H

#include "motor.h"
#include "node.h"

class LIB_API Mesh : public Node {
public:
    // Constructor
    Mesh() {};

    Mesh(const std::string& name, const glm::mat4& matrix, unsigned int children,
        const std::string& targetName, bool isSkinned, const std::string& subtypeName,
        const std::string& materialName, float radius, const glm::vec3& bBoxMin,
        const glm::vec3& bBoxMax, bool hasPhysics);

    void printData() const override;

    // Getters
    bool isSkinned() const;  // Mark this as const as it does not modify the object
    std::string getSubtypeName() const;
    std::string getMaterialName() const;
    float getRadius() const;
    glm::vec3 getBoundingBoxMin() const;
    glm::vec3 getBoundingBoxMax() const;
    bool hasPhysics() const;  // Mark this as const as well

private:
    bool isSkinned_;
    std::string subtypeName_;
    std::string materialName_;
    float radius_;
    glm::vec3 bBoxMin_, bBoxMax_;
    bool hasPhysics_;
    // Add other physics properties if needed
};

#endif // MESH_H
