#include "light.h"

#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

/**
 * @class DirectionalLight
 * @brief Represents a directional light in a 3D scene.
 *
 * Inherits from Light class. Directional lights simulate light sources that
 * are far away (like the sun) and emit light rays that are parallel and in a
 * single direction. This class provides functionalities to set up and render
 * a directional light in a scene.
 */
class LIB_API DirectionalLight : public Light {

public:
    /**
     * @brief Constructor for DirectionalLight class.
     *
     * Initializes a new instance of the DirectionalLight class with specified
     * properties.
     *
     * @param id An integer representing the ID of the light.
     * @param name A std::string representing the name of the light.
     * @param lightNumber An integer representing the light number in the scene.
     * @param ambient A glm::vec4 representing the ambient color of the light.
     * @param diffuse A glm::vec4 representing the diffuse color of the light.
     * @param specular A glm::vec4 representing the specular color of the light.
     */
    DirectionalLight(const int id, const std::string name, const int lightNumber,
        const glm::vec4 ambient, const glm::vec4 diffuse,
        const glm::vec4 specular);

    /**
     * @brief Destructor for DirectionalLight.
     *
     * Cleans up resources used by the DirectionalLight instance.
     * As this is a simple destructor, no additional operations are performed.
     */
    ~DirectionalLight() {};

public:
    /**
     * @brief Renders the directional light.
     *
     * Implements the render method from the Light class. This method is used
     * to render the directional light in the scene using the provided camera
     * inverse matrix.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

    /**
     * @brief Sets the transformation matrix for the light.
     *
     * Overrides the setTransform method from the Light class. This method is
     * used to apply a transformation to the directional light.
     *
     * @param transform A glm::mat4 representing the transformation matrix.
     */
    void setTransform(glm::mat4 transform) override;
};

#endif // DIRECTIONAL_LIGHT
