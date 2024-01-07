#pragma once
#include "material.h"
#include "mesh.h"
#include "node.h"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>
#include <math.h>
#include <vector>

#ifndef GAME
#define GAME

/**
 * @class Game
 * @brief Represents the core game logic and state in a 3D game environment.
 *
 * This class encapsulates the main game mechanics, including car movement, game state management,
 * and interaction with game objects like teapots. It handles the update logic, win condition checks,
 * and manages the grid where the game objects are placed.
 */
class Game {
public:
    /**
     * @brief Constructor for Game class.
     *
     * Initializes a new Game instance with specified game objects and their positions.
     *
     * @param cars A vector of Node pointers representing the cars in the game.
     * @param originalCarPosition A vector of vectors representing the original positions of the cars.
     * @param teapot A pointer to the Node representing the teapot.
     * @param brokenTeaPot A pointer to the Node representing the broken teapot.
     */
    Game(std::vector<Node*> cars,
        std::vector<std::vector<int>> originalCarPosition, Node* teapot,
        Node* brokenTeaPot);

    /**
     * @brief Destructor for Game class.
     *
     * Cleans up resources used by the Game instance.
     */
    ~Game();

public:
    /**
     * @brief Moves the active car in the specified direction.
     *
     * @param direction A glm::vec2 representing the direction of movement.
     */
    void moveCar(glm::vec2 direction);

    /**
     * @brief Sets the movement speed of the cars.
     *
     * @param movementSpeed A float representing the new movement speed.
     */
    void setMovementSpeed(float movementSpeed);

    /**
     * @brief Gets the current movement speed of the cars.
     *
     * @return A float representing the current movement speed.
     */
    float getMovementSpeed();

    /**
     * @brief Sets the active car that can be controlled.
     *
     * @param activeCar An integer representing the index of the active car.
     */
    void setActiveCar(int activeCar);

    /**
     * @brief Gets the index of the active car.
     *
     * @return An integer representing the index of the active car.
     */
    int getActiveCar();

    /**
     * @brief Updates the game state.
     *
     * This method should be called regularly to update the game state, including checking for win conditions.
     */
    void update();

    /**
     * @brief Resets the game to its initial state.
     *
     * This method resets the game, including the positions of the cars and the game state.
     */
    void reset();

    bool isRunning = true; ///< Flag indicating whether the game is currently running.

private:
    std::vector<Node*> cars; ///< Vector storing the cars in the game.
    std::vector<glm::vec3> carsPosition; ///< Vector storing the current positions of the cars.
    std::vector<glm::mat4> carsOriginalTransform; ///< Vector storing the original transformations of the cars.
    std::vector<std::vector<int>> grid; ///< Grid representing the game board.
    std::vector<std::vector<int>> originalCarPosition; ///< Vector storing the original positions of the cars in the grid.
    Node* teaPot; ///< Pointer to the teapot node.
    Node* brokenTeaPot; ///< Pointer to the broken teapot node.

    Game* originalGame; ///< Pointer to the original game state for reset purposes.

    glm::vec3 getOrientation(const Node* node);
    bool moveCarOnGrid(glm::vec2 direction);
    void printGrid();
    void biLux();
    void win();
    void swapTeaPot();
    void updateCarEmission(int carIndex, const glm::vec4& emission);

    glm::vec4 baseEmissionOff = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 baseEmissionOn = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f) * 2.0f;
    float elapsedTime = 0.0f;
    float glowDuration = 1.0f;
    bool isGlowingUp = true;

    float movementSpeed = 1.0f;
    int activeCar = 0;

    bool isWinning = false;
};

#endif // GAME
