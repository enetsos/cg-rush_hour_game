#include "node.h"
#include "object.h"
#include <list>

#ifndef LIST
#define LIST

/**
 * @class List
 * @brief Manages a collection of Node objects for rendering and interaction.
 *
 * Inherits from the Object class. This class is designed to handle a list of Node objects,
 * providing functionalities to add, render, and manage these nodes in a 3D graphics environment.
 */
class LIB_API List : public Object {
public:
    /**
     * @brief Constructor for the List class.
     *
     * Initializes a new instance of the List class. The constructor is empty as the initialization
     * of the list is handled automatically.
     */
    List() {}

    /**
     * @brief Adds a Node to the list.
     *
     * @param node A pointer to the Node object to be added to the list.
     */
    void addEntry(Node* node);

    /**
     * @brief Renders all Node objects in the list.
     *
     * @param cameraMatrix A glm::mat4 representing the camera matrix used for rendering.
     */
    void render(glm::mat4 cameraMatrix) override;

    /**
     * @brief Clears the list of all Node objects.
     *
     * This method removes all Node objects from the list, potentially freeing memory.
     */
    void clear();

    /**
     * @brief Retrieves a Node object from the list by its index.
     *
     * @param i The index of the Node object in the list.
     * @return A pointer to the requested Node object, or nullptr if the index is out of range.
     */
    Node* getObject(int i);

    /**
     * @brief Gets the number of Node objects in the list.
     *
     * @return An integer representing the number of Node objects in the list.
     */
    int size();

private:
    std::list<Node*> objectsList; ///< A list of pointers to Node objects.
};

#endif // LIST
