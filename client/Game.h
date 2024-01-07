#pragma once
#include "node.h"
#include "mesh.h"
#include "material.h"
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
  Game(std::vector<Node *> cars, std::vector<std::vector<int>> originalCarPosition, Node* teapot, Node* brokenTeaPot);
  ~Game();

public:
  void moveCar(glm::vec2 direction);
  void setMovementSpeed(float movementSpeed);
  float getMovementSpeed();
  void setActiveCar(int activeCar);
  int getActiveCar();
  void update();
  void reset();

  bool isRunning = true;


private:
  std::vector<Node *> cars;
  std::vector<glm::vec3> carsPosition;
  std::vector<glm::mat4> carsOriginalTransform;
  std::vector<std::vector<int>> grid;
  std::vector<std::vector<int>> originalCarPosition;
  Node* teaPot;
  Node* brokenTeaPot;

  Game* originalGame;

  glm::vec3 getOrientation(const Node *node);
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