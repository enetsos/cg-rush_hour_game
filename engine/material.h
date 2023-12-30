#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "node.h"
#include "motor.h"
#include <string>

class LIB_API Material{
public:
    // Constructor with parameters
    Material(const std::string& name, const glm::vec3& emission, const glm::vec3& albedo, float roughness, float metalness, float alpha,
        const std::string& textureName, const std::string& normalMapName, const std::string& heightMapName,
        const std::string& roughnessMapName, const std::string& metalnessMapName);

    void printData() const;

    // Getters
    string getName() const;
    glm::vec3 getEmission() const;
    glm::vec3 getAlbedo() const;
    float getRoughness() const;
    float getMetalness() const;
    float getAlpha() const;
    std::string getTextureName() const;
    std::string getNormalMapName() const;
    std::string getHeightMapName() const;
    std::string getRoughnessMapName() const;
    std::string getMetalnessMapName() const;

    
private:

    string name;
    glm::vec3 emission;
    glm::vec3 albedo;
    float roughness;
    float metalness;
    float alpha;
    std::string textureName;
    std::string normalMapName;
    std::string heightMapName;
    std::string roughnessMapName;
    std::string metalnessMapName;
};

#endif // MATERIAL_H
