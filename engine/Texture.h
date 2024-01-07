#include "object.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#ifndef TEXTURE
#define TEXTURE

/**
 * @class Texture
 * @brief Represents a texture in a 3D graphics environment.
 *
 * Inherits from Object. This class encapsulates the properties and functionalities related to a texture,
 * including its ID, anisotropic filtering capabilities, and texture file handling. It is used to manage and
 * apply textures to objects in the scene.
 */
class LIB_API Texture : public Object {

public:
    /**
     * @brief Constructor for Texture class.
     *
     * Initializes a new Texture instance with a specified ID and name.
     *
     * @param id An integer representing the ID of the texture.
     * @param name A std::string representing the name of the texture.
     */
    Texture(int id, const std::string name);

    /**
     * @brief Destructor for Texture class.
     *
     * Cleans up resources used by the Texture instance.
     */
    ~Texture();

public:
    /**
     * @brief Renders the texture.
     *
     * Overrides the render method from the Object class. This method is used to apply the texture
     * in the scene using the provided camera inverse matrix.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

    /**
     * @brief Sets the texture ID using the specified file.
     *
     * @param file A std::string representing the path of the texture file.
     */
    void setTexId(std::string file);

    /**
     * @brief Static method to set the default path for texture files.
     *
     * @param path A std::string representing the default path for texture files.
     */
    static void setPath(std::string path);

private:
    unsigned int texId = 0; ///< The texture ID.
    bool isAnisotropicSupported = false; ///< Flag indicating if anisotropic filtering is supported.
    int anisotropicLevel = 1; ///< The level of anisotropic filtering.
    static std::string path; ///< Static variable storing the default path for texture files.
};

#endif // TEXTURE
