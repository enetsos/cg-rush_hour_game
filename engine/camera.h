#include "Projection.h"
#include "node.h"

#ifndef CAMERA
#define CAMERA

/**
 * @class Camera
 * @brief Represents a camera in a 3D environment.
 *
 * This class inherits from Node and is responsible for handling camera-related operations.
 * It encapsulates a projection and provides functionality to get the inverse of a matrix
 * and to access the projection details.
 */
class LIB_API Camera : public Node {
public:
    /**
     * @brief Constructor for Camera class.
     *
     * Initializes a new instance of the Camera class with an ID, name, and projection.
     *
     * @param id An integer representing the ID of the camera.
     * @param name A std::string representing the name of the camera.
     * @param projection A pointer to a Projection object associated with this camera.
     */
    Camera(int id, const std::string name, Projection* projection);

    /**
     * @brief Destructor for Camera class.
     *
     * Cleans up resources used by the Camera instance.
     */
    ~Camera();

public:
    /**
     * @brief Gets the Projection object associated with this camera.
     *
     * @return A pointer to the Projection object.
     */
    Projection* getProjection();

    /**
     * @brief Calculates and returns the inverse of a matrix.
     *
     * @return A glm::mat4 representing the inverse matrix.
     */
    glm::mat4 getInverse();

private:
    Projection* projection; ///< A pointer to the Projection object associated with this camera.
};

#endif // CAMERA
