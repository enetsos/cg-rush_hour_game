// light.cpp

#include "light.h"

Light::Light(string _name) : Node(_name), lightColor(glm::vec3(1.0f)), intensity(1.0f) {
    // Additional constructor initialization if needed
}

void Light::setLightColor(glm::vec3 color) {
    lightColor = color;
}

glm::vec3 Light::getLightColor() const {
    return lightColor;
}

void Light::setIntensity(float value) {
    intensity = value;
}

float Light::getIntensity() const {
    return intensity;
}

bool Light::render(glm::mat4 m) {
    // Implementation of rendering logic goes here
    // You can use lightColor, intensity, and m in your rendering code

    // Returning a placeholder value for demonstration purposes
    return true;
}
