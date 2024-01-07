#include "LibDef.h"
#include <glm/glm.hpp>

#ifndef VERTEX
#define VERTEX

/**
 * @class Vertex
 * @brief Represents a vertex in a 3D graphics environment.
 *
 * This class encapsulates the properties of a vertex, including its position, normal, and texture coordinates.
 * It is used in the construction of 3D meshes and other geometric primitives.
 */
class LIB_API Vertex {

public:
    /**
     * @brief Constructor for Vertex class.
     *
     * Initializes a new Vertex instance with specified position and normal vectors.
     *
     * @param position A glm::vec3 representing the position of the vertex.
     * @param normal A glm::vec3 representing the normal vector of the vertex.
     */
    Vertex(glm::vec3 position, glm::vec3 normal);

    /**
     * @brief Destructor for Vertex class.
     *
     * Cleans up resources used by the Vertex instance.
     */
    ~Vertex();

public:
    /**
     * @brief Gets the position of the vertex.
     *
     * @return A glm::vec3 representing the position of the vertex.
     */
    glm::vec3 getPosition();

    /**
     * @brief Gets the normal vector of the vertex.
     *
     * @return A glm::vec3 representing the normal vector of the vertex.
     */
    glm::vec3 getNormal();

    /**
     * @brief Gets the texture coordinates of the vertex.
     *
     * @return A glm::vec2 representing the texture coordinates of the vertex.
     */
    glm::vec2 getTextureCoordinates();

    /**
     * @brief Sets the texture coordinates of the vertex.
     *
     * @param textCoord A glm::vec2 representing the new texture coordinates of the vertex.
     */
    void setTextureCoordinates(glm::vec2 textCoord);

private:
    glm::vec3 position; ///< The position of the vertex.
    glm::vec3 normal; ///< The normal vector of the vertex.
    glm::vec2 textureCoordinates; ///< The texture coordinates of the vertex.
};

#endif // VERTEX
