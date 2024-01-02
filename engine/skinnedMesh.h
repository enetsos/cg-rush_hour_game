#pragma once
#ifndef SKINNED_H
#define SKINNED_H

#include "motor.h"
#include "mesh.h"
#include "bone.h"
#include <vector>
#include <string>

class SkinnedMesh : public Mesh {
public:
    // Constructor
    SkinnedMesh(const std::string& name,
        const glm::mat4& matrix,
        unsigned int children,
        const std::string& targetName,
        const std::string& subtypeName,
        const std::string& materialName,
        float radius,
        const glm::vec3& bBoxMin,
        const glm::vec3& bBoxMax,
        bool hasPhysics,
        const PhysProps& physProps,
        const std::vector<Hull>& hulls,
        const std::vector<LOD>& lods,
        const glm::mat4& poseMatrix,
        const std::vector<Bone>& bones);

    // Specific methods for skinned meshes
    void setPoseMatrix(const glm::mat4& matrix);
    void addBone(const std::string& name, const glm::mat4& matrix);

    // Overrides
    void printData() const override;

private:
    glm::mat4 poseMatrix_;
    vector<Bone> bones_;
};

#endif // SKINNED_H
