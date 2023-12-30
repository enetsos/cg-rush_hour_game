// Material.cpp

#include "material.h"
#include "GL/freeglut.h"

// Constructor implementation
Material::Material(const std::string& name, const glm::vec3& emission, const glm::vec3& albedo,
    float roughness,float metalness, float alpha, const std::string& textureName,
    const std::string& normalMapName, const std::string& heightMapName,
    const std::string& roughnessMapName, const std::string& metalnessMapName)
    :
    name(name),emission(emission), albedo(albedo), roughness(roughness), metalness(metalness), alpha(alpha),
    textureName(textureName), normalMapName(normalMapName), heightMapName(heightMapName),
    roughnessMapName(roughnessMapName), metalnessMapName(metalnessMapName) {}

void Material::printData() const{
    cout << "material]" << endl;

std::cout << "Name: " << name << std::endl;
	std::cout << "Emission: " << emission.r << " " << emission.g << " " << emission.b << std::endl;
	std::cout << "Albedo: " << albedo.r << " " << albedo.g << " " << albedo.b << std::endl;
	std::cout << "Roughness: " << roughness << std::endl;
	std::cout << "Metalness: " << metalness << std::endl;
	std::cout << "Alpha: " << alpha << std::endl;
	std::cout << "Texture: " << textureName << std::endl;
	std::cout << "Normal Map: " << normalMapName << std::endl;
	std::cout << "Height Map: " << heightMapName << std::endl;
	std::cout << "Roughness Map: " << roughnessMapName << std::endl;
	std::cout << "Metalness Map: " << metalnessMapName << std::endl;
}

string Material::getName() const {
	return name;
}

glm::vec3 Material::getEmission() const {
    return emission;
}

glm::vec3 Material::getAlbedo() const {
    return albedo;
}

float Material::getRoughness() const {
    return roughness;
}

float Material::getMetalness() const {
	return metalness;
}

float Material::getAlpha() const {
    return alpha;
}

std::string Material::getTextureName() const {
    return textureName;
}

std::string Material::getNormalMapName() const {
    return normalMapName;
}

std::string Material::getHeightMapName() const {
    return heightMapName;
}

std::string Material::getRoughnessMapName() const {
    return roughnessMapName;
}

std::string Material::getMetalnessMapName() const {
    return metalnessMapName;
}

