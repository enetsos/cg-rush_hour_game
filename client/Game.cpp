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

    // Assuming the orientation.y (yaw) determines whether the car is vertical or horizontal
    // Adjust the threshold angle as needed
    float thresholdAngle = 45.0f; // degrees

    glm::vec3 movementDirection;

    if (std::abs(orientation.y) < thresholdAngle || std::abs(orientation.y) > (180.0f - thresholdAngle)) {
        
        // The car is oriented vertically, move up/down
        movementDirection = glm::vec3(0.0f, direction.y, 0.0f);

    }
    else {
        // The car is oriented horizontally, move left/right
        movementDirection = glm::vec3(0.0f, direction.x, 0.0f);
    }

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