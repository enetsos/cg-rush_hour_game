// light.cpp
#include "light.h"
#include <GL/freeglut.h>

Light::Light(std::string _name) : Node(_name), lightColor(glm::vec3(1.0f)), intensity(1.0f) {}

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

bool Light::render(glm::mat4 viewProjection) {
    // Set up the light's position in world space
    glm::vec4 lightPositionWorld = matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Set up the model-view-projection matrix for the light
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(lightPositionWorld));
    glm::mat4 mvpMatrix = viewProjection * modelMatrix;

    // Render the light as a small sphere
    glColor3f(lightColor.r, lightColor.g, lightColor.b);
    glutSolidSphere(0.1f, 20, 20);

    return true;
}
