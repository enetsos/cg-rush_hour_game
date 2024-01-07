#include "OrthogonalProjection.h"
#include <string>
#include <vector>

#ifndef UI_PROJECTION
#define UI_PROJECTION

/**
 * @class UIProjection
 * @brief Represents a user interface projection in a 3D graphics environment.
 *
 * Inherits from OrthogonalProjection. This class is specialized for handling user interface projections,
 * which typically involve orthogonal projection for 2D rendering. It provides functionalities for managing UI
 * elements like labels and their colors.
 */
class LIB_API UIProjection : public OrthogonalProjection {
public:
    /**
     * @brief Constructor for UIProjection with width and height.
     *
     * Initializes a new instance of the UIProjection class with default projection boundaries
     * based on the specified width and height.
     *
     * @param width An integer representing the width of the projection.
     * @param heigth An integer representing the height of the projection.
     */
    UIProjection(int width, int heigth);

    /**
     * @brief Constructor for UIProjection with custom boundaries.
     *
     * Initializes a new instance of the UIProjection class with specified projection boundaries.
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
    UIProjection(int width, int heigth, float left, float right, float bottom,
        float top, float zNear, float zFar);

    /**
     * @brief Destructor for UIProjection.
     *
     * Cleans up resources used by the UIProjection instance.
     */
    ~UIProjection();

public:
    /**
     * @brief Sets the color for UI elements.
     *
     * @param color A glm::vec3 representing the color to be set for UI elements.
     */
    void setColor(glm::vec3 color);

    /**
     * @brief Adds a label to the UI.
     *
     * @param label A std::string representing the label to be added.
     */
    void addLabel(std::string label);

    /**
     * @brief Edits a label at the specified index.
     *
     * @param index An integer representing the index of the label to be edited.
     * @param label A std::string representing the new text of the label.
     */
    void editLabel(int index, std::string label);

    /**
     * @brief Clears all labels from the UI.
     */
    void clear();

    /**
     * @brief Prints the UI elements to the screen.
     *
     * This method handles the rendering of UI elements like labels.
     */
    void print();

private:
    std::vector<std::string> labels; ///< A vector storing the labels for the UI.
    glm::vec3 color{ 1.0f }; ///< The color of the UI elements.
};

#endif // UI_PROJECTION
