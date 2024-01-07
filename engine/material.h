#include "Texture.h"
#include "object.h"

#ifndef MATERIAL
#define MATERIAL

/**
 * @class Material
 * @brief Represents a material in a 3D graphics environment.
 *
 * Inherits from the Object class. This class encapsulates material properties such as emission, ambient,
 * diffuse, specular components, and shininess, which are used to determine how the material interacts with light.
 * It also supports texture mapping.
 */
class LIB_API Material : public Object {

public:
    /**
     * @brief Constructor for Material class with emission.
     *
     * Initializes a new instance of the Material class with specified properties, including emission.
     *
     * @param id An integer representing the ID of the material.
     * @param name A std::string representing the name of the material.
     * @param emission A glm::vec4 representing the emission color of the material.
     * @param ambient A glm::vec4 representing the ambient color of the material.
     * @param diffuse A glm::vec4 representing the diffuse color of the material.
     * @param specular A glm::vec4 representing the specular color of the material.
     * @param shininess A float representing the shininess of the material.
     */
    Material(int id, const std::string name, glm::vec4 emission,
        glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
        float shininess);

    /**
     * @brief Constructor for Material class without emission.
     *
     * Initializes a new instance of the Material class with specified properties, excluding emission.
     *
     * @param id An integer representing the ID of the material.
     * @param name A std::string representing the name of the material.
     * @param ambient A glm::vec4 representing the ambient color of the material.
     * @param diffuse A glm::vec4 representing the diffuse color of the material.
     * @param specular A glm::vec4 representing the specular color of the material.
     * @param shininess A float representing the shininess of the material.
     */
    Material(int id, const std::string name, glm::vec4 ambient, glm::vec4 diffuse,
        glm::vec4 specular, float shininess);

    /**
     * @brief Destructor for Material class.
     *
     * Cleans up resources used by the Material instance.
     */
    ~Material();

public:
    /**
     * @brief Renders the material.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

    /**
     * @brief Gets the emission color of the material.
     *
     * @return A glm::vec4 representing the emission color.
     */
    glm::vec4 getEmission();

    /**
     * @brief Gets the ambient color of the material.
     *
     * @return A glm::vec4 representing the ambient color.
     */
    glm::vec4 getAmbient();

    /**
     * @brief Gets the diffuse color of the material.
     *
     * @return A glm::vec4 representing the diffuse color.
     */
    glm::vec4 getDiffuse();

    /**
     * @brief Gets the specular color of the material.
     *
     * @return A glm::vec4 representing the specular color.
     */
    glm::vec4 getSpecular();

    /**
     * @brief Gets the shininess of the material.
     *
     * @return A float representing the shininess.
     */
    float getShininess();

    /**
     * @brief Sets the texture of the material.
     *
     * @param t A pointer to the Texture object to be associated with this material.
     */
    void setTexture(Texture* t);

    /**
     * @brief Gets the texture of the material.
     *
     * @return A pointer to the Texture object associated with this material.
     */
    Texture* getTexture();

    /**
     * @brief Sets the emission color of the material.
     *
     * @param emission A glm::vec4 representing the emission color to be set.
     */
    void setEmission(glm::vec4 emission);

    /**
     * @brief Sets the shininess of the material.
     *
     * @param shininess A float representing the shininess to be set.
     */
    void setShininess(float shininess);

private:
    glm::vec4 emission; ///< Emission color component of the material.
    glm::vec4 ambient; ///< Ambient color component of the material.
    glm::vec4 diffuse; ///< Diffuse color component of the material.
    glm::vec4 specular; ///< Specular color component of the material.
    float shininess; ///< Shininess factor of the material.
    Texture* texture; ///< Pointer to the Texture object associated with this material.
};

#endif // MATERIAL
