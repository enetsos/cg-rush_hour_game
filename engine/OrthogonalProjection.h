#include "Projection.h"

#ifndef ORTHOGONAL_PROJECTION
#define ORTHOGONAL_PROJECTION

/**
 * @class OrthogonalProjection
 * @brief Represents an orthogonal projection in a 3D graphics environment.
 *
 * Inherits from Projection class. This class encapsulates the properties and functionalities of an orthogonal
 * (or orthographic) projection, which is a method of projecting three-dimensional objects into a two-dimensional
 * plane, where the projection lines are parallel to each other and perpendicular to the plane of projection.
 */
class LIB_API OrthogonalProjection : public Projection {
public:
    /**
     * @brief Constructor for OrthogonalProjection with width and height.
     *
     * Initializes a new instance of the OrthogonalProjection class with default projection boundaries
     * based on the specified width and height.
     *
     * @param width An integer representing the width of the projection.
     * @param heigth An integer representing the height of the projection.
     */
    OrthogonalProjection(int width, int heigth);

    /**
     * @brief Constructor for OrthogonalProjection with custom boundaries.
     *
     * Initializes a new instance of the OrthogonalProjection class with specified projection boundaries.
     *
     * @param width An integer representing the width of the projection.
     * @param heigth An integer representing the height of the projection.
     * @param left A float representing the left boundary of the projection.
     * @param right A float representing the right boundary of the projection.
     * @param bottom A float representing the bottom boundary of the projection.
     * @param top A float representing the top boundary of the projection.
     * @param zNear A float representing the near clipping plane.
     * @param zFar A float representing the far clipping plane.
     */
    OrthogonalProjection(int width, int heigth, float left, float right,
        float bottom, float top, float zNear, float zFar);

    /**
     * @brief Destructor for OrthogonalProjection.
     *
     * Cleans up resources used by the OrthogonalProjection instance.
     */
    ~OrthogonalProjection();

public:
    /**
     * @brief Updates the projection matrix based on current properties.
     *
     * Overrides the update method from the Projection class. This method recalculates
     * the projection matrix using the current orthogonal projection parameters.
     */
    void update() override;

private:
    float left; ///< Left boundary of the orthogonal projection.
    float right; ///< Right boundary of the orthogonal projection.
    float bottom; ///< Bottom boundary of the orthogonal projection.
    float top; ///< Top boundary of the orthogonal projection.
    float zNear; ///< Near clipping plane of the orthogonal projection.
    float zFar; ///< Far clipping plane of the orthogonal projection.
};

#endif // ORTHOGONAL_PROJECTION
