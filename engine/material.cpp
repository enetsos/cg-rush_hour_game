#include <GL/freeglut.h>
#include "material.h"
bool LIB_API Material::render(glm::mat4 m) {
	m += glm::mat4{ 0.0f };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, powf(2.0f, shininess));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
	return true;
}
