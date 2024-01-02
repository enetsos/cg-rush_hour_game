#include "skinnedMesh.h"

// Constructor
SkinnedMesh::SkinnedMesh(const std::string& name,
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
    const std::vector<Bone>& bones)
    : Mesh(name, matrix, children, targetName, true, subtypeName, materialName,
        radius, bBoxMin, bBoxMax, hasPhysics, physProps, hulls, lods),
    poseMatrix_(poseMatrix),
    bones_(bones){}

void SkinnedMesh::setPoseMatrix(const glm::mat4& matrix) {
    poseMatrix_ = matrix;
}


void SkinnedMesh::printData() const {
    // First, call the printData of the base Mesh class
    Mesh::printData();

    // Print bone information
    std::cout << "   Bones: " << bones_.size() << std::endl;
    for (const auto& bone : bones_) {
        std::cout << "      Bone Name: " << bone.boneName << std::endl;
        std::cout << "      Bone Pose Matrix:\n";
        
        // Additional bone information (like inverse bind matrix, weights, etc.) can be printed here
    }
}
