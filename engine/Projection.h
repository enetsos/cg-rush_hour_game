#include "LibDef.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef PROJECTION
#define PROJECTION

/**
 * @class Projection
 * @brief Represents a projection matrix used in a 3D graphics environment.
 *
 * This class serves as a base for creating different types of projection matrices, such as orthogonal or perspective.
 * It provides functionalities to set and get the projection matrix, update projection settings, and manage projection dimensions.
 */
class LIB_API Projection {
public:
    /**
     * @brief Constructor for Projection class.
     *
     * Initializes a new Projection instance with specified width and height.
     *
     * @param width An integer representing the width of the projection.
     * @param heigth An integer representing the height of the projection.
     */
    Projection(int width, int heigth);

    /**
     * @brief Destructor for Projection class.
     *
     * Cleans up resources used by the Projection instance.
     */
    ~Projection();

public:
    /**
     * @brief Sets the current OpenGL projection.
     *
     * This method updates the OpenGL projection settings based on the current projection matrix.
     */
    void setOpenGLProjection();

    /**
     * @brief Sets the projection matrix.
     *
     * @param projection A glm::mat4 representing the new projection matrix.
     */
    void setProjection(glm::mat4 projection);

    /**
     * @brief Gets the current projection matrix.
     *
     * @return A glm::mat4 representing the current projection matrix.
     */
    glm::mat4 getProjection();

    /**
     * @brief Virtual method for updating the projection matrix.
     *
     * This method can be overridden in derived classes to update the projection matrix based on specific projection types.
     */
    virtual void update();

    /**
     * @brief Gets the width of the projection.
     *
     * @return An integer representing the width of the projection.
     */
    int getWidth();

    /**
     * @brief Gets the height of the projection.
     *
     * @return An integer representing the height of the projection.
     */
    int getHeigth();

    /**
     * @brief Sets the width of the projection.
     *
     * @param width An integer representing the new width of the projection.
     */
    void setWidth(int width);

    /**
     * @brief Sets the height of the projection.
     *
     * @param heigth An integer representing the new height of the projection.
     */
    void setHeigth(int heigth);

private:
    glm::mat4 projection{ 1.0f }; ///< The current projection matrix.
    int width;                  ///< The width of the projection.
    int heigth;                 ///< The height of the projection.
};

#endif // PROJECTION
