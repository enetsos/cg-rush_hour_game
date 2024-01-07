#include "Projection.h"

#ifndef PERSPECTIVE_PROJECTION
#define PERSPECTIVE_PROJECTION

/**
 * @class PerspectiveProjection
 * @brief Represents a perspective projection in a 3D graphics environment.
 *
 * Inherits from Projection class. This class encapsulates the properties and functionalities of a perspective
 * projection, which is a method of projecting three-dimensional objects into a two-dimensional plane,
 * where the projection lines converge in a single point (the vanishing point), simulating the depth perception of the human eye.
 */
class LIB_API PerspectiveProjection : public Projection {
public:
    /**
     * @brief Constructor for PerspectiveProjection.
     *
     * Initializes a new instance of the PerspectiveProjection class with specified properties.
     *
     * @param width An integer representing the width of the projection.
     * @param heigth An integer representing the height of the projection.
     * @param fov A float representing the field of view angle in degrees.
     * @param near A float representing the near clipping plane.
     * @param far A float representing the far clipping plane.
     */
    PerspectiveProjection(int width, int heigth, float fov = 45.0f, float near = 1.0f, float far = 100.0f);

    /**
     * @brief Destructor for PerspectiveProjection.
     *
     * Cleans up resources used by the PerspectiveProjection instance.
     */
    ~PerspectiveProjection();

public:
    /**
     * @brief Updates the projection matrix based on current properties.
     *
     * Overrides the update method from the Projection class. This method recalculates
     * the projection matrix using the current perspective projection parameters.
     */
    void update() override;

private:
    float fov;   ///< Field of view angle in degrees.
    float near_; ///< Near clipping plane distance.
    float far_;  ///< Far clipping plane distance.
};

#endif //PERSPECTIVE_PROJECTION
