#include "light.h"

// Constructor
Light::Light(const std::string& name, const glm::mat4& matrix, unsigned int children, const std::string& targetName,
    string subType, const glm::vec3& color, const glm::vec3& direction,
    float radius, float cutoff, float spotExponent, unsigned char castShadows, unsigned char isVolumetric)
    : Node(name, matrix, children, targetName), subType(subType), color(color), direction(direction),
    radius(radius), cutoff(cutoff), spotExponent(spotExponent), castShadows(castShadows), isVolumetric(isVolumetric)
{
    // Constructor body (if needed)
}

void Light::printData() const {
    Node::printData(); // Call base class implementation

    // Additional details specific to Light
    cout << "   Light Subtype : " << subType << endl;
    cout << "   Color : " << glm::to_string(color) << endl;
    cout << "   Direction : " << glm::to_string(direction) << endl;
    cout << "   Radius : " << radius << endl;
    cout << "   Cutoff : " << cutoff << endl;
    cout << "   Spot Exponent : " << spotExponent << endl;
    cout << "   Cast Shadows : " << static_cast<int>(castShadows) << endl;
    cout << "   Volumetric : " << static_cast<int>(isVolumetric) << endl;
}


// Getters
string Light::getSubType() const {
    return subType;
}

glm::vec3 Light::getColor() const {
    return color;
}

glm::vec3 Light::getDirection() const {
    return direction;
}

float Light::getRadius() const {
    return radius;
}

float Light::getCutoff() const {
    return cutoff;
}

float Light::getSpotExponent() const {
    return spotExponent;
}

unsigned char Light::getCastShadows() const {
    return castShadows;
}

unsigned char Light::getIsVolumetric() const {
    return isVolumetric;
}
