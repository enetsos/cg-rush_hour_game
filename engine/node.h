#include "object.h"
#include <string>
#include <vector>

#ifndef NODE
#define NODE

/**
 * @class Node
 * @brief Represents a node in a scene graph for a 3D graphics environment.
 *
 * Inherits from Object. This class is a fundamental part of the scene graph, representing a node that can
 * have child nodes and a parent node. It handles operations such as rendering, hierarchy management,
 * transformation, and spatial queries.
 */
class LIB_API Node : public Object {

public:
    /**
     * @brief Constructor for Node class.
     *
     * Initializes a new Node instance with a specified ID and name.
     *
     * @param id An integer representing the ID of the node.
     * @param name A std::string representing the name of the node.
     */
    Node(int id, const std::string name);

    /**
     * @brief Constructor for Node class with a parent node.
     *
     * Initializes a new Node instance with a specified ID, name, and parent node.
     *
     * @param id An integer representing the ID of the node.
     * @param name A std::string representing the name of the node.
     * @param parent A pointer to the parent Node.
     */
    Node(int id, const std::string name, Node* parent);

    /**
     * @brief Destructor for Node class.
     *
     * Cleans up resources used by the Node instance.
     */
    ~Node();

public:
    /**
     * @brief Renders the node and its children.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    void render(glm::mat4 cameraInv) override;

    /**
     * @brief Finds a child node by its ID.
     *
     * @param id The ID of the child node to find.
     * @return A pointer to the Node if found, nullptr otherwise.
     */
    Node* findById(const int id);

    /**
     * @brief Finds a child node by its name.
     *
     * @param name The name of the child node to find.
     * @return A pointer to the Node if found, nullptr otherwise.
     */
    Node* findByName(const std::string name);

    /**
     * @brief Removes a child node by its ID.
     *
     * @param id The ID of the child node to remove.
     */
    void removeById(const int id);

    /**
     * @brief Removes a child node by its name.
     *
     * @param name The name of the child node to remove.
     */
    void removeByName(const std::string name);

    /**
     * @brief Removes all child nodes of this node.
     */
    void removeChildren();

    /**
     * @brief Gets the N-th child node.
     *
     * @param n The index of the child node to retrieve.
     * @return A pointer to the N-th child Node, nullptr if the index is out of range.
     */
    Node* getNthChild(int n) const;

    /**
     * @brief Adds a child node.
     *
     * @param child A pointer to the Node to add as a child.
     */
    void addChild(Node* child);

    /**
     * @brief Removes the N-th child node.
     *
     * @param n The index of the child node to remove.
     */
    void removeNthChild(int n);

    /**
     * @brief Gets the number of child nodes.
     *
     * @return An integer representing the number of children.
     */
    int getNumberOfChildren() const;

    /**
     * @brief Sets the parent of this node.
     *
     * @param parent A pointer to the new parent Node.
     */
    void setParent(Node* parent);

    /**
     * @brief Gets the parent of this node.
     *
     * @return A pointer to the parent Node, nullptr if there is no parent.
     */
    Node* getParent() const;

    /**
     * @brief Gets the local transformation matrix of this node.
     *
     * @return A glm::mat4 representing the local transformation.
     */
    glm::mat4 getTransform() const;

    /**
     * @brief Sets the local transformation matrix of this node.
     *
     * @param transform A glm::mat4 representing the new local transformation.
     */
    virtual void setTransform(glm::mat4 transform);

    /**
     * @brief Gets the final transformation matrix, including parent transformations.
     *
     * @return A glm::mat4 representing the final transformation matrix.
     */
    glm::mat4 getFinalMatrix() const;

    /**
     * @brief Gets the world position of this node.
     *
     * @return A glm::vec3 representing the world position.
     */
    glm::vec3 getWorldPosition() const;

    /**
     * @brief Sets the world position of this node.
     *
     * @param position A glm::vec3 representing the new world position.
     */
    virtual void setWorldPosition(glm::vec3 position);

private:
    std::vector<Node*> children; ///< A vector of pointers to child nodes.
    Node* parent; ///< A pointer to the parent node.
    glm::mat4 transform = glm::mat4(1.0f); ///< The local transformation matrix of the node.
};

#endif // NODE
