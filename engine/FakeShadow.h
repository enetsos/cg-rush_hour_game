#pragma once
#include "mesh.h"
#include <math.h>

#ifndef FAKESHADOW
#define FAKESHADOW

/**
 * @class FakeShadow
 * @brief Represents a fake shadow for a 3D object.
 *
 * Inherits from Mesh class. This class is used to create and manage fake shadows in a 3D environment.
 * It allows the creation of shadows that are not physically accurate but visually effective for certain
 * rendering scenarios. It links with a specific model and can be manipulated in terms of offset and scaling.
 */
class LIB_API FakeShadow : public Mesh {
public:
    /**
     * @brief Constructor for FakeShadow class.
     *
     * Initializes a new instance of the FakeShadow class with specified properties.
     *
     * @param id An integer representing the ID of the shadow.
     * @param name A std::string representing the name of the shadow.
     * @param material A shared_ptr to Material to be used for the shadow.
     * @param model A pointer to the Mesh object that this shadow is associated with.
     */
    FakeShadow(const int id, const std::string name,
        std::shared_ptr<Material> material, Mesh* model);

    /**
     * @brief Destructor for FakeShadow.
     *
     * Cleans up resources used by the FakeShadow instance.
     */
    ~FakeShadow();

public:
    /**
     * @brief Renders the fake shadow.
     *
     * Implements the render method from the Mesh class. This method is used to render the fake shadow
     * in the scene using the provided camera inverse matrix.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

    /**
     * @brief Sets the offset matrix for the shadow.
     *
     * @param offset A glm::mat4 representing the offset matrix.
     */
    void setOffset(glm::mat4 offset);

    /**
     * @brief Gets the current offset matrix of the shadow.
     *
     * @return A glm::mat4 representing the offset matrix.
     */
    glm::mat4 getOffset() const;

    /**
     * @brief Gets the scaling matrix for the shadow.
     *
     * @return A glm::mat4 representing the scaling matrix.
     */
    glm::mat4 getScaling() const;

    /**
     * @brief Sets the parent mesh for the shadow.
     *
     * @param node A pointer to the Mesh object that will be the parent of this shadow.
     */
    void setShadowParent(Mesh* node);

private:
    /**
     * @brief Calculates and returns the rotation matrix for the shadow.
     *
     * @return A glm::mat4 representing the rotation matrix.
     */
    glm::mat4 getRotationMatrix();

private:
    glm::mat4 offset; ///< Offset matrix for the shadow.
    glm::mat4 scaling; ///< Scaling matrix for the shadow.
    Mesh* model; ///< Pointer to the model associated with this shadow.
};

#endif // FAKESHADOW
