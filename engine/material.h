#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "object.h"
#include "motor.h"


class LIB_API Material {
public:
    Material();

    void setAmbient(const glm::vec4& ambient);
    void setDiffuse(const glm::vec4& diffuse);
    void setSpecular(const glm::vec4& specular);
    void setShininess(float shininess);

    void apply();

private:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
};

#endif // MATERIAL_H
