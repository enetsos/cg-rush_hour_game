#include "Game.h"

Game::Game(std::vector<Node*> cars) : cars(cars) {
    for (auto& car : cars)
        carsOriginalTransform.push_back(car->getTransform());

};

Game::~Game() {};

void Game::setMovementSpeed(float movementSpeed) {
    this->movementSpeed = movementSpeed;
}

float Game::getMovementSpeed() {
    return movementSpeed;
}

void Game::setActiveCar(int activeCar) {
    if (activeCar >= cars.size() || activeCar < 0)
        return;

    this->activeCar = activeCar;
}

int Game::getActiveCar() {
    return activeCar;
}

void Game::moveCar(glm::vec2 direction) {
    Node* car = cars.at(activeCar);

    // Get the car's orientation in Euler angles
    glm::vec3 orientation = getOrientation(car);

    // Convert the Euler angles back to a quaternion
    glm::quat carOrientation = glm::quat(glm::radians(orientation));

    // Assuming the forward direction is along the Z-axis
    // If it's along another axis, use glm::vec3(1, 0, 0) for the X-axis or glm::vec3(0, 1, 0) for the Y-axis
    glm::vec3 forwardDirection = glm::vec3(0.0f, 0.0f, 1.0f);

    // Rotate the forward direction by the car's orientation
    glm::vec3 orientedForward = carOrientation * forwardDirection;

    // Calculate movement direction (forward/backward)
    // direction.x is used for forward/backward movement; direction.y is ignored in this context
    glm::vec3 movementDirection = orientedForward * direction.x;

    // Apply the translation
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), movementDirection * movementSpeed);

    // Update the car's transform
    car->setTransform(car->getTransform() * translation);
}

glm::vec3 Game::getOrientation(const Node* node) {
    glm::mat4 transform = node->getTransform();

    // Decompose the transformation matrix
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::quat rotation;
    glm::decompose(transform, scale, rotation, translation, skew, perspective);

    // Convert quaternion to Euler angles
    glm::vec3 eulerAngles = glm::eulerAngles(rotation);

    // Convert radians to degrees if necessary
    eulerAngles = glm::degrees(eulerAngles);

    return eulerAngles;
}


void Game::update() {
    // Any additional logic required for each update cycle
}