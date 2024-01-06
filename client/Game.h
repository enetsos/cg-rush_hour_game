#pragma once
#include "node.h"
#include "mesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/matrix_decompose.hpp>
#include <gtx/string_cast.hpp>
#include <math.h>
#include <vector>
#include <chrono>

#ifndef GAME
#define GAME

class Game {
public:
  Game(std::vector<Node *> cars, std::vector<std::vector<int>> originalCarPosition);
  ~Game();

public:
  void moveCar(glm::vec2 direction);
  void setMovementSpeed(float movementSpeed);
  float getMovementSpeed();
  void setActiveCar(int activeCar);
  int getActiveCar();
  void update();

private:
  std::vector<Node *> cars;
  std::vector<glm::vec3> carsPosition;
  std::vector<glm::mat4> carsOriginalTransform;
  std::vector<std::vector<int>> grid;
  std::vector<std::vector<int>> originalCarPosition;

  glm::vec3 getOrientation(const Node *node);
  bool moveCarOnGrid(glm::vec2 direction);
  void printGrid();
  void biLux();

  std::chrono::high_resolution_clock::time_point lastUpdateTime;
  float glowDuration = 1.0f;
  bool isGlowingUp = true;

  float movementSpeed = 1.0f;
  int activeCar = 0;
};

#endif // GAME