// Material.cpp

#include "material.h"
#include "GL/freeglut.h"

// Constructor with default material properties
Material::Material()
    : ambient(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)),
      diffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)),
      specular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), shininess(128.0f) {}

void Material::setAmbient(const glm::vec4 &amb) { ambient = amb; }

void Material::setDiffuse(const glm::vec4 &diff) { diffuse = diff; }

void Material::setSpecular(const glm::vec4 &spec) { specular = spec; }

void Material::setShininess(float shin) { shininess = shin; }

void Material::apply() {
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
