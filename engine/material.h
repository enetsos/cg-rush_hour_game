#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "object.h"
#include "motor.h"
using namespace glm;
class LIB_API Material : public Object {

private:
	float shininess;
	vec4 ambient{ 0.5f, 0.5f, 0.5f, 1.0f };
	vec4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
	vec4 diffuse{ 0.5f, 0.5f, 0.5f, 1.0f };
	// Add other material properties

public:
	Material(string _name) : Object(_name), shininess(32.0f) {}

	virtual ~Material() {}

	float getShininess() const {
		return shininess;
	}
	//add other methods
	vec4 getAmbient() {
		return ambient;
	}
	vec4 getSpecular() {
		return specular;
	}
	vec4 getDiffuse() {
		return diffuse;
	}
	bool render(glm::mat4 m) override;
};

#endif // MATERIAL_H
