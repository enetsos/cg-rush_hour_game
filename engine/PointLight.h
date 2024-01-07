#include "light.h"

#ifndef POINT_LIGHT
#define POINT_LIGHT

/**
 * @class PointLight
 * @brief Represents a point light source in a 3D graphics environment.
 *
 * Inherits from Light class. This class encapsulates the properties and functionalities of a point light source,
 * which emits light in all directions from a single point. It includes properties for ambient, diffuse,
 * and specular lighting as well as a cutoff value for the light's influence.
 */
class LIB_API PointLight : public Light {

public:
    /**
     * @brief Constructor for PointLight class.
     *
     * Initializes a new instance of the PointLight class with specified properties.
     *
     * @param id An integer representing the ID of the light.
     * @param name A std::string representing the name of the light.
     * @param lightNumber An integer representing the light number in the scene.
     * @param ambient A glm::vec4 representing the ambient color of the light.
     * @param diffuse A glm::vec4 representing the diffuse color of the light.
     * @param specular A glm::vec4 representing the specular color of the light.
     * @param cutOff A float representing the cutoff angle for the light's influence (in degrees).
     */
    PointLight(const int id, const std::string name, const int lightNumber,
        const glm::vec4 ambient, const glm::vec4 diffuse,
        const glm::vec4 specular, const float cutOff = 180.0f);

    /**
     * @brief Destructor for PointLight.
     *
     * Cleans up resources used by the PointLight instance.
     */
    ~PointLight() {};

public:
    /**
     * @brief Renders the point light.
     *
     * Overrides the render method from the Light class. This method is used to render the point light
     * in the scene using the provided camera inverse matrix.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    virtual void render(glm::mat4 cameraInv) override;

private:
    float cutOff; ///< Cutoff angle for the light's influence (in degrees).
};

#endif // POINT_LIGHT
