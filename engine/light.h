#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "node.h"
#include "motor.h"

class LIB_API Light : public Node {
private:
    glm::vec3 lightColor;
    float intensity;

public:

    Light(string _name);

    void setLightColor(glm::vec3 color);

    glm::vec3 getLightColor() const;

    void setIntensity(float value);

    float getIntensity() const;

    virtual bool render(glm::mat4 m) override;
};

#endif // LIGHT_H