#include "node.h"
#include <algorithm>

#ifndef LIGHT
#define LIGHT

/**
 * @class Light
 * @brief Represents a light source in a 3D scene.
 *
 * Inherits from the Node class. This class encapsulates properties and behaviors of a light source,
 * including ambient, diffuse, and specular lighting components, as well as attenuation factors. It also
 * supports setting and getting the light's position in the scene.
 */
class LIB_API Light : public Node {

public:
    /**
     * @brief Constructor for Light class.
     *
     * Initializes a new instance of the Light class with specified properties.
     *
     * @param id An integer representing the ID of the light.
     * @param name A std::string representing the name of the light.
     * @param lightNumber An integer representing the light number in the scene.
     * @param ambient A glm::vec4 representing the ambient color of the light.
     * @param diffuse A glm::vec4 representing the diffuse color of the light.
     * @param specular A glm::vec4 representing the specular color of the light.
     */
    Light(const int id, const std::string name, const int lightNumber,
        const glm::vec4 ambient, const glm::vec4 diffuse,
        const glm::vec4 specular);

    /**
     * @brief Destructor for Light class.
     *
     * Cleans up resources used by the Light instance.
     */
    ~Light();

public:
    /**
     * @brief Gets the light number.
     *
     * @return An integer representing the light number.
     */
    int getLightNumber();

    /**
     * @brief Sets the position of the light to a default value.
     */
    void setPosition();

    /**
     * @brief Sets the position of the light.
     *
     * @param pos A glm::vec4 representing the position of the light.
     */
    void setPosition(glm::vec4 pos);

    /**
     * @brief Gets the position of the light.
     *
     * @return A glm::vec4 representing the position of the light.
     */
    glm::vec4 getPosition();

    /**
     * @brief Gets the next available light number.
     *
     * @return An integer representing the next light number.
     */
    static int getNextLightNumber();

    /**
     * @brief Renders the light.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    virtual void render(glm::mat4 cameraInv) override;

    /**
     * @brief Sets the transformation matrix for the light.
     *
     * @param transform A glm::mat4 representing the transformation matrix.
     */
    virtual void setTransform(glm::mat4 transform) override;

    /**
     * @brief Gets the constant attenuation factor.
     *
     * @return A float representing the constant attenuation.
     */
    float getConstantAttenuation();

    /**
     * @brief Gets the linear attenuation factor.
     *
     * @return A float representing the linear attenuation.
     */
    float getLinearAttenuation();

    /**
     * @brief Gets the quadratic attenuation factor.
     *
     * @return A float representing the quadratic attenuation.
     */
    float getQuadraticAttenuation();

    /**
     * @brief Sets the constant attenuation factor.
     *
     * @param constantAttenuation A float representing the constant attenuation to be set.
     */
    void setConstantAttenuation(float constantAttenuation);

    /**
     * @brief Sets the linear attenuation factor.
     *
     * @param linearAttenuation A float representing the linear attenuation to be set.
     */
    void setLinearAttenuation(float linearAttenuation);

    /**
     * @brief Sets the quadratic attenuation factor.
     *
     * @param quadraticAttenuation A float representing the quadratic attenuation to be set.
     */
    void setQuadraticAttenuation(float quadraticAttenuation);

private:
    static int nextNumber; ///< Static counter to keep track of the next light number.
    int lightNumber; ///< The light number in the scene.
    glm::vec4 ambient; ///< Ambient color component of the light.
    glm::vec4 diffuse; ///< Diffuse color component of the light.
    glm::vec4 specular; ///< Specular color component of the light.
    glm::vec4 position{ 0.0f, 0.0f, 0.0f, 1.0f }; ///< Position of the light in the scene.

    float constantAttenuation = 1.0f; ///< Constant attenuation factor for the light.
    float linearAttenuation = 0.0f; ///< Linear attenuation factor for the light.
    float quadraticAttenuation = 0.0f; ///< Quadratic attenuation factor for the light.
};

#endif // LIGHT
