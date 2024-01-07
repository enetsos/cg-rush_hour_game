#include "LibDef.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <string>

#ifndef OBJECT
#define OBJECT

/**
 * @class Object
 * @brief Base class for objects in a 3D graphics environment.
 *
 * This class serves as a base for various objects in a 3D graphics context.
 * It provides fundamental attributes like ID and name, along with a basic render method.
 * It is designed to be extended by other specific classes that require these basic properties.
 */
class LIB_API Object {

public:
    /**
     * @brief Default constructor for Object class.
     *
     * Initializes a new Object instance with a unique ID.
     */
    Object() : id(Object::getNextId()) {}

    /**
     * @brief Constructor for Object class with specified ID and name.
     *
     * Initializes a new Object instance with a given ID and name.
     *
     * @param id An integer representing the ID of the object.
     * @param name A std::string representing the name of the object.
     */
    Object(int id, const std::string name);

    /**
     * @brief Destructor for Object class.
     *
     * Cleans up resources used by the Object instance.
     */
    ~Object();

public:
    /**
     * @brief Gets the ID of the object.
     *
     * @return An integer representing the ID of the object.
     */
    int getId() const;

    /**
     * @brief Gets the name of the object.
     *
     * @return A std::string representing the name of the object.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the object.
     *
     * @param name A std::string representing the new name of the object.
     */
    void setName(const std::string name);

    /**
     * @brief Static method to get the next available ID for an object.
     *
     * @return An integer representing the next available ID.
     */
    static int getNextId();

    /**
     * @brief Virtual render method for the object.
     *
     * @param cameraInv A glm::mat4 representing the inverse of the camera's matrix.
     */
    virtual void render(glm::mat4 cameraInv);

private:
    static int nextId; ///< Static variable to keep track of the next available ID.
    const int id; ///< The unique ID of the object.
    std::string name; ///< The name of the object.
};

#endif // OBJECT
