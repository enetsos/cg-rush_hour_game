#include "Game.h"

Game::Game(std::vector<Node*> cars, std::vector<std::vector<int>> originalCarPosition, Node* teaPot, Node* brokenTeaPot) : cars(cars), originalCarPosition(originalCarPosition), teaPot(teaPot), brokenTeaPot(brokenTeaPot){
    for (auto& car : cars)
        carsOriginalTransform.push_back(car->getTransform());

    // 6x6 grid
    grid = originalCarPosition;

    // set emission of teapot
    std::shared_ptr<Material> material = dynamic_cast<Mesh*>(teaPot)->getMaterial();
    if (material) {
		glm::vec4 baseEmission = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f); 
		material->setEmission(baseEmission);
	}

    material = dynamic_cast<Mesh*>(brokenTeaPot)->getMaterial();
    if (material) {
        glm::vec4 baseEmission = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f); 
        material->setEmission(baseEmission);
    }

    // low emission of cars
    for (auto& car : cars) {
		material = dynamic_cast<Mesh*>(car)->getMaterial();
        if (material) {
			material->setShininess(-5.0f);
		}
	}

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


    if(!moveCarOnGrid(direction))
		return;

    printGrid();
    // Apply the translation
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), movementDirection * movementSpeed);

    // Update the car's transform
    car->setTransform(car->getTransform() * translation);
}

bool Game::moveCarOnGrid(glm::vec2 direction) {
    // for grid
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.at(i).size(); j++) {
            if (grid.at(i).at(j) == activeCar) {
                switch (activeCar){
                case 0:
                    // if grid is out of bound
                    if (direction.x < 0) {
                        printf("J: %d\n", j);


                        if (j + 2 >= grid[i].size()) {
                            isWinning = true;
                            return true;
                        }
                            


                        // move right
                        if (grid[i][j + 2] == -1) {
                            grid[i][j] = -1;
                            grid[i][j + 2] = activeCar;
                            return true;
                        }

                    }
                    else if (direction.x > 0) {
                        if (j - 1 < 0)
                            return false;
                        // move left
                        if (grid[i][j - 1] == -1 && direction.x > 0) {
                            grid[i][j + 1] = -1;
                            grid[i][j - 1] = activeCar;
                            return true;
                        }
                    }
                    return false;

                case 2:
                case 4:
                    if (direction.x < 0) {
                        if (j + 2 > grid[i].size()) 
                            return false;

                        // move right
                        if (grid[i][j + 2] == -1) {
                            grid[i][j] = -1;
                            grid[i][j + 2] = activeCar;
                            return true;
                        }

                    }
                    else if (direction.x > 0) {
                        if (j - 1 < 0)
                            return false;
                        // move left
                        if (grid[i][j - 1] == -1 && direction.x > 0) {
						    grid[i][j + 1] = -1;
						    grid[i][j - 1] = activeCar;
						    return true;
					    }
                    }                    
                    return false;
                case 1:
                case 3:
                    if (direction.y < 0) {
                        if (i + 2 >= grid.size())
                            return false;

                        if (grid[i + 2][j] == -1) {
                            grid[i][j] = -1;
                            grid[i + 2][j] = activeCar;
                            return true;
                        }
                    }
                    else if (direction.y > 0) {
                        if (i - 1 < 0)
                            return false;

                        if (grid[i - 1][j] == -1) {
                            grid[i + 1][j] = -1;
                            grid[i - 1][j] = activeCar;
                            return true;
                        }
                    }
                    return false;

                case 6:
                case 7:
                    if (direction.x < 0) {
                        if (j + 3 >= grid[i].size())
                            return false;

                        if (grid[i][j + 3] == -1) {
                            grid[i][j] = -1;
                            grid[i][j + 3] = activeCar;
                            return true;
                        }
                    }
                    else if (direction.x > 0) {
                        if (j - 1 < 0)
                            return false;

                        if (grid[i][j - 1] == -1) {
                            grid[i][j + 2] = -1;
                            grid[i][j - 1] = activeCar;
                            return true;
                        }
                    }
                    return false;

                case 5:
                    if (direction.y < 0) {
                        if (i + 3 >= grid.size())
                            return false;

                        if (grid[i + 3][j] == -1) {
                            grid[i][j] = -1;
                            grid[i + 3][j] = activeCar;
                            return true;
                        }
                    }
                    else if (direction.y > 0) {
                        if (i - 3 < 0)
                            return false;

                        if (grid[i - 3][j] == -1) {
                            grid[i + 3][j] = -1;
                            grid[i - 3][j] = activeCar;
                            return true;
                        }
                    }
                    return false;
                                
                default:
                    break;
                };
			}
		}
	}
}

void Game::printGrid() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.at(i).size(); j++) {
			std::cout << grid.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
    std::cout << std::endl;

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

void Game::biLux() {
    if (elapsedTime >= glowDuration) {
        elapsedTime -= glowDuration;
        isGlowingUp = !isGlowingUp;
    }

    float glowIntensity = isGlowingUp ? (elapsedTime / glowDuration) : (1.0f - elapsedTime / glowDuration);

    updateCarEmission(activeCar, baseEmissionOn * glowIntensity);
    updateCarEmission(activeCar == 0 ? cars.size() - 1 : activeCar - 1, baseEmissionOff);
}

void Game::updateCarEmission(int carIndex, const glm::vec4& emission) {
    Node* carNode = cars.at(carIndex);
    Mesh* carMesh = dynamic_cast<Mesh*>(carNode); // Consider optimizing this
    if (carMesh) {
        std::shared_ptr<Material> material = carMesh->getMaterial();
        if (material && material->getEmission() != emission) {
            material->setEmission(emission);
        }
    }
}

void Game::win() {

    if (glm::distance(cars.at(activeCar)->getTransform()[3], teaPot->getTransform()[3]) < 85.0f) {
        // Update the car's transform
        cars.at(activeCar)->setTransform(cars.at(activeCar)->getTransform() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f * movementSpeed)));
    }
    else {
        swapTeaPot();
        isRunning = false;
    }

}

void Game::update() {
    elapsedTime += 0.05f;

    biLux();

    if (isWinning)
        win();
}

void Game::swapTeaPot() {
    

    // Get the current transformation matrix
    glm::mat4 transform = teaPot->getTransform();
    glm::mat4 transformOld = brokenTeaPot->getTransform();

    
    // Set the new transformation matrix
    brokenTeaPot->setTransform(transform);
    teaPot->setTransform(transformOld);
    
}
