#include "PointLight.h"

#ifndef SPOT_LIGHT
#define SPOT_LIGHT

/**
 * @class SpotLight
 * @brief Represents a spot light source in a 3D graphics environment.
 *
 * Inherits from PointLight class. This class encapsulates the properties and functionalities of a spot light source,
 * which emits light in a specific direction with a conical spread. It includes properties for ambient, diffuse,
 * and specular lighting as well as a cutoff value for the light's influence and the direction of the light.
 */
class LIB_API SpotLight : public PointLight {

public:
    /**
     * @brief Constructor for SpotLight class.
     *
     * Initializes a new instance of the SpotLight class with specified properties.
     *
     * @param id An integer representing the ID of the light.
     * @param name A std::string representing the name of the light.
     * @param lightNumber An integer representing the light number in the scene.
     * @param ambient A glm::vec4 representing the ambient color of the light.
     * @param diffuse A glm::vec4 representing the diffuse color of the light.
     * @param specular A glm::vec4 representing the specular color of the light.
     * @param cutOff A float representing the cutoff angle for the light's influence (in degrees).
     * @param direction A glm::vec3 representing the direction of the light.
     */
    SpotLight(const int id, const std::string name, const int lightNumber,
        const glm::vec4 ambient, const glm::vec4 diffuse,
        const glm::vec4 specular, const float cutOff,
        const glm::vec3 direction);

    /**
     * @brief Destructor for SpotLight.
     *
     * Cleans up resources used by the SpotLight instance.
     */
    ~SpotLight() {};

public:
    /**
     * @brief Renders the spot light.
     *
     * Overrides the render method from the PointLight class. This method is used to render the spot light
     * in the scene using the provided camera inverse matrix.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

private:
    glm::vec3 direction; ///< The direction of the spot light.
};

#endif // SPOT_LIGHT
