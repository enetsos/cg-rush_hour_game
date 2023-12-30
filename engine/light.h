#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "node.h"
#include "OvLight.h" // Assuming this is the correct include for OvLight
#include "motor.h"

class LIB_API Light : public Node {
public:
    // Constructor
    Light(const std::string& name, const glm::mat4& matrix, unsigned int children, const std::string& targetName,
        string subType, const glm::vec3& color, const glm::vec3& direction,
        float radius, float cutoff, float spotExponent, unsigned char castShadows, unsigned char isVolumetric);

    void printData() const override;

    // Getters
    string getSubType() const;
    glm::vec3 getColor() const;
    glm::vec3 getDirection() const;
    float getRadius() const;
    float getCutoff() const;
    float getSpotExponent() const;
    unsigned char getCastShadows() const;
    unsigned char getIsVolumetric() const;

private:
    string subType;
    glm::vec3 color, direction;
    float radius, cutoff, spotExponent;
    unsigned char castShadows, isVolumetric;
};

#endif // LIGHT_H