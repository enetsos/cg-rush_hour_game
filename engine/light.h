#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "node.h"
#include "motor.h"

enum class LightType {
    Point,
    Directional,
    Spotlight
};

class LIB_API Light : public Node{
public:
    Light(LightType type);

    void setAmbient(const glm::vec4& amb);
    void setDiffuse(const glm::vec4& diff);
    void setSpecular(const glm::vec4& spec);
    void setIntensity(float inten);
    void setDirection(const glm::vec3& dir);
    void setCutoff(float co);
    void setAttenuation(float constant, float linear, float quadratic);

    void render();

private:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float intensity;
    glm::vec3 direction;
    float cutoff;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    LightType lightType;
};

#endif // LIGHT_H