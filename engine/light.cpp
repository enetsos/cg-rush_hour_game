#include "light.h"
#include "GL/freeglut.h"

Light::Light(LightType type) : lightType(type) {
    // Initialize with default values
    setPosition(glm::vec3(0.0f, -3.0f, -30.0f));
    ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    intensity = 1.0f;
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
    cutoff = 180.0f; // Default for a point light
    constantAttenuation = 1.0f;
    linearAttenuation = 0.0f;
    quadraticAttenuation = 0.0f;
}

void Light::render() {
    GLenum lightID = GL_LIGHT0; // This should be dynamic for multiple lights

    glEnable(lightID);

    // Set light properties
    glLightfv(lightID, GL_AMBIENT, glm::value_ptr(ambient));
    glLightfv(lightID, GL_DIFFUSE, glm::value_ptr(diffuse));
    glLightfv(lightID, GL_SPECULAR, glm::value_ptr(specular));

    if (lightType == LightType::Directional) {
        glm::vec4 directionHomogeneous(direction, 0.0f); // Directional lights use w = 0
        glLightfv(lightID, GL_POSITION, glm::value_ptr(directionHomogeneous));
    }
    else {
        glm::vec4 positionHomogeneous(getPosition(), 1.0f); // Point/Spotlights use w = 1
        glLightfv(lightID, GL_POSITION, glm::value_ptr(positionHomogeneous));
    }

    // Draw a small emissive sphere at the light's position
    glPushMatrix(); // Save current matrix state
    glTranslatef(getPosition().x, getPosition().y, getPosition().z); // Move to light position
    glColor3f(1.0f, 1.0f, 0.0f); // Set sphere color (e.g., yellow)
    glutSolidSphere(0.2f, 16, 16); // Draw a small sphere
    glPopMatrix(); // Restore the matrix state


    // Additional setup for spotlights if necessary
    if (lightType == LightType::Spotlight) {
        glLightfv(lightID, GL_SPOT_DIRECTION, glm::value_ptr(direction));
        glLightf(lightID, GL_SPOT_CUTOFF, cutoff);
    }

    // Attenuation factors for point lights and spotlights
    if (lightType == LightType::Point || lightType == LightType::Spotlight) {
        glLightf(lightID, GL_CONSTANT_ATTENUATION, constantAttenuation);
        glLightf(lightID, GL_LINEAR_ATTENUATION, linearAttenuation);
        glLightf(lightID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    }
}
