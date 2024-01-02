#pragma once
#ifndef MESH_H
#define MESH_H

#include "motor.h"
#include "node.h"
#include "physProp.h"
#include "hull.h"
#include "lod.h"




class LIB_API Mesh : public Node {
public:
    // Constructor
    Mesh() = default;

    Mesh(const std::string& name,
        const glm::mat4& matrix,
        unsigned int children,
        const std::string& targetName,
        bool isSkinned,
        const std::string& subtypeName,
        const std::string& materialName,
        float radius,
        const glm::vec3& bBoxMin,
        const glm::vec3& bBoxMax,
        bool hasPhysics,
        const PhysProps& physProps,
        const std::vector<Hull>& hulls,
        const std::vector<LOD>& lods);


    void printData() const override;

    // Getters
    bool isSkinned() const;  // Mark this as const as it does not modify the object
    std::string getSubtypeName() const;
    std::string getMaterialName() const;
    float getRadius() const;
    glm::vec3 getBoundingBoxMin() const;
    glm::vec3 getBoundingBoxMax() const;
    bool hasPhysics() const;  // Mark this as const as well
    PhysProps getPhysProps() const { return physProps_; }
    vector<Hull> getHulls() const { return hulls_; }
    vector<LOD> getLODs() const { return lods_; }

    void initializeBuffers();  // To initialize OpenGL buffers
    void render() const;       // To render the mesh


private:
    bool isSkinned_;
    std::string subtypeName_;
    std::string materialName_;
    float radius_;
    glm::vec3 bBoxMin_, bBoxMax_;
    bool hasPhysics_;
    PhysProps physProps_;
    vector<Hull> hulls_;
    vector<LOD> lods_;
    
};

#endif // MESH_H
