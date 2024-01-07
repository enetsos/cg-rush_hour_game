#include "Vertex.h"
#include "material.h"
#include "node.h"

#ifndef MESH
#define MESH

/**
 * @class Mesh
 * @brief Represents a 3D mesh in a graphics environment.
 *
 * Inherits from Node. This class encapsulates a 3D mesh, which is a collection of vertices, and a material.
 * It provides functionalities to add vertices, render the mesh, and manage its material and shadow casting properties.
 */
class LIB_API Mesh : public Node {

public:
    /**
     * @brief Constructor for Mesh class.
     *
     * Initializes a new instance of the Mesh class with specified properties.
     *
     * @param id An integer representing the ID of the mesh.
     * @param name A std::string representing the name of the mesh.
     * @param material A shared_ptr to a Material object associated with this mesh.
     */
    Mesh(const int id, const std::string name,
        std::shared_ptr<Material> material);

    /**
     * @brief Destructor for Mesh class.
     *
     * Cleans up resources used by the Mesh instance.
     */
    ~Mesh();

public:
    /**
     * @brief Adds a vertex to the mesh.
     *
     * @param v A pointer to the Vertex object to be added.
     * @param lod An integer representing the level of detail at which this vertex is added.
     */
    void addVertex(Vertex* v, int lod);

    /**
     * @brief Renders the mesh.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    virtual void render(glm::mat4 cameraInv) override;

    /**
     * @brief Gets the shadow casting property of the mesh.
     *
     * @return A boolean value indicating whether the mesh casts shadows.
     */
    virtual bool getCastShadow() const;

    /**
     * @brief Sets the shadow casting property of the mesh.
     *
     * @param castShadow A boolean value indicating whether the mesh should cast shadows.
     */
    virtual void setCastShadow(bool castShadow);

    /**
     * @brief Retrieves the vertices of the mesh for a specific level of detail.
     *
     * @param lod An integer representing the level of detail.
     * @return A vector of pointers to Vertex objects.
     */
    std::vector<Vertex*> getVertices(int lod);

    /**
     * @brief Gets the material associated with the mesh.
     *
     * @return A shared_ptr to the Material object associated with this mesh.
     */
    std::shared_ptr<Material> getMaterial();

protected:
    int lod = 0; ///< Current level of detail.
    std::vector<std::vector<Vertex*>> vertices; ///< A nested vector storing vertices at different levels of detail.
    std::shared_ptr<Material> material; ///< Shared pointer to the material associated with this mesh.

private:
    bool castShadow = true; ///< Boolean flag indicating whether the mesh casts shadows.
};

#endif // MESH
