#include "mesh.h"

// Constructor implementation
Mesh::Mesh(const std::string& name, const glm::mat4& matrix, unsigned int children,
    const std::string& targetName, bool isSkinned, const std::string& subtypeName,
    const std::string& materialName, float radius, const glm::vec3& bBoxMin,
    const glm::vec3& bBoxMax, bool hasPhysics)
    : Node(name, matrix, children, targetName),
    isSkinned_(isSkinned),
    subtypeName_(subtypeName),
    materialName_(materialName),
    radius_(radius),
    bBoxMin_(bBoxMin),
    bBoxMax_(bBoxMax),
    hasPhysics_(hasPhysics) {}

void Mesh::printData() const{
    Node::printData();
    
    cout << "   Is skinned . .:  " << (int)isSkinned_ << endl;
    cout << "   Subtype . . . :  " << subtypeName_ << endl;
    cout << "   Material  . . :  " << materialName_ << endl;
    cout << "   Radius  . . . :  " << radius_ << endl;
    cout << "   BBox minimum  :  " << bBoxMin_.x << ", " << bBoxMin_.y << ", " << bBoxMin_.z << endl;
    cout << "   BBox maximum  :  " << bBoxMax_.x << ", " << bBoxMax_.y << ", " << bBoxMax_.z << endl;
    cout << "   Physics . . . :  " << (int)hasPhysics_ << endl;

}

// Getters
bool Mesh::isSkinned() const { return isSkinned_; }
std::string Mesh::getSubtypeName() const { return subtypeName_; }
std::string Mesh::getMaterialName() const { return materialName_; }
float Mesh::getRadius() const { return radius_; }
glm::vec3 Mesh::getBoundingBoxMin() const { return bBoxMin_; }
glm::vec3 Mesh::getBoundingBoxMax() const { return bBoxMax_; }
bool Mesh::hasPhysics() const { return hasPhysics_; }
