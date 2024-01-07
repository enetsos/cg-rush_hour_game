//////////////
// #INCLUDE //
//////////////

// Library header:
#include "engine.h"
#include "Game.h"

// C/C++:
#include <glm.hpp>
#include <iostream>
#include <iterator>
#include <vector>

//////////
// MAIN //
//////////

Engine engine;
UIProjection *ui;

float cameraX = 70.0f;
float cameraY = 100.0f;
float cameraZ = 0.0f;
float rotationX = 45.0f;
float rotationY = 70.0f;
float rotationZ = -45.0f;
float cameraSpeed = 2.0f;
float rotationSpeed = 2.0f;

float stationaryCameraX = 10.0f;
float stationaryCameraY = 190.0f;
float stationaryCameraZ = 12.0f;
float stationaryRotationX = -90.0f;
float stationaryRotationY = 0.0f;
float stationaryRotationZ = 90.0f;

Node *root;
bool isActive = true;
bool showUI = true;
Game* game;

float movementDistance = 82.0f;

Camera *freeCamera = nullptr;
Camera *stationaryCamera = nullptr;
Camera *activeCamera = nullptr;

void keyboardCallback(int key) {

  if (activeCamera == freeCamera) {
    switch (key) {
      // Free camera movement
    case 'w':
      cameraX--;
      break;
    case 's':
      cameraX++;
      break;
    case 'a':
      cameraZ++;
      break;
    case 'd':
        cameraZ--;
      break;
    case 'e':
      cameraY++;
      break;
    case 'q':
      cameraY--;
      break;

      // Free camera rotation
    case '8':
      rotationY--;
      break;
    case '2':
        rotationY++;
      break;
    case '6':
      rotationX++;
      break;
    case '4':
      rotationX--;
      break;
    case '7':
      rotationZ--;
      break;
    case '9':
      rotationZ++;
      break;
    }
  }

  switch (key) {

    // Camera management
  case 'c':
    activeCamera = (activeCamera == freeCamera ? stationaryCamera : freeCamera);
    engine.setCamera(activeCamera);
    break;

  case 'r':
      game->reset();
      break;

    // Application controls
  case '.':
    isActive = false;
    break;
  case KEY_F1:
    showUI = !showUI;
    break;

    // Robot arm controls
  case '+':
      game->setActiveCar((game->getActiveCar() + 8 + 1) % 8);
    break;
  case '-':
      game->setActiveCar((game->getActiveCar() + 8 - 1) % 8);
    break;
  case KEY_UP:
      game->moveCar(glm::vec2(0.0f, movementDistance));
      break;
  case KEY_DOWN:
      game->moveCar(glm::vec2(0.0f, -movementDistance));
      break;
  case KEY_RIGHT:
      game->moveCar(glm::vec2(-movementDistance, 0.0f));
      break;
  case KEY_LEFT:
      game->moveCar(glm::vec2(movementDistance, 0.0f));
      break;
  case ' ':
    break;
  }
}

void displayCallback() {
  // Clear the screen:
  glm::vec3 color(37.0f, 53.0f, 87.0f);
  engine.clean(glm::vec4(color.r / 255, color.g / 255, color.b / 255, 1.0f));

  // Set projection
  activeCamera->getProjection()->setOpenGLProjection();
  if (activeCamera == freeCamera) {
    glm::mat4 translation_cam = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f + cameraX, 0.0f + cameraY, 0.0f + cameraZ) *
            cameraSpeed);
    glm::mat4 rotationX_cam =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotationX * rotationSpeed),
                    glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY_cam =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotationY * rotationSpeed),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ_cam =
        glm::rotate(glm::mat4(1.0f), glm::radians(rotationZ * rotationSpeed),
                    glm::vec3(0.0f, 0.0f, 1.0f));
    activeCamera->setTransform(translation_cam * rotationX_cam * rotationY_cam *
                               rotationZ_cam);

  }
  if (game->isRunning) {
    ui->editLabel(11, ""); 
    game->update();
  }
  else
      ui->editLabel(11, "You won!");

  // draw scene
  engine.getList().render(activeCamera->getInverse());

  if (showUI) {
    ui->editLabel(0, "FPS: " + std::to_string(engine.getFps()));
    ui->editLabel(2, "[+/-] - Switch car: " + std::to_string(game->getActiveCar() + 1));
    ui->editLabel(
        3, "[c] - change camera: " +
               std::string(activeCamera == freeCamera ? "free" : "stationary"));

    if (activeCamera == freeCamera) {
        ui->editLabel(7, "[w/a/s/d] - move camera");
        ui->editLabel(8, "[q/e] - camera down/up");
        ui->editLabel(9, "[8/4/2/6] - rotate camera");
        ui->editLabel(10, "[9/7] - camera zoom");
    }
    else
    {
        ui->editLabel(7, "");
		ui->editLabel(8, "");
		ui->editLabel(9, "");
		ui->editLabel(10, "");
    }

    
    ui->print();
  }

  // Swap this context's buffer:
  engine.swap();

  // Force rendering refresh:
  engine.forceRefresh();
}

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[]) {
  engine = Engine();
  engine.setTexturePath("./scene/");
  engine.init("Rush Hour", keyboardCallback, displayCallback);
  root = engine.loadScene("./scene/ProjectScene.OVO");

  freeCamera = (Camera *)root->findByName("freeCamera");
  stationaryCamera = (Camera *)root->findByName("stationaryCamera");
  activeCamera = stationaryCamera;
  glm::mat4 translation_cam =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + stationaryCameraX,
                                                0.0f + stationaryCameraY,
                                                0.0f + stationaryCameraZ));
  glm::mat4 rotationX_cam =
      glm::rotate(glm::mat4(1.0f), glm::radians(stationaryRotationX),
                  glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rotationY_cam =
      glm::rotate(glm::mat4(1.0f), glm::radians(stationaryRotationY),
                  glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rotationZ_cam =
      glm::rotate(glm::mat4(1.0f), glm::radians(stationaryRotationZ),
                  glm::vec3(0.0f, 0.0f, 1.0f));
  activeCamera->setTransform(translation_cam * rotationX_cam * rotationY_cam *
                             rotationZ_cam);

  // Set where the fake shadows will be projected
  Mesh *floor = (Mesh *)root->findByName("Floor");
  Mesh *table = (Mesh *)root->findByName("Table");

  ((FakeShadow *)root->findByName("Table_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("Teapot_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("BrokenTeaPot_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Sphere_shadow"))->setShadowParent(floor);

  ((FakeShadow *)root->findByName("Car001_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car002_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car003_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car004_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car005_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car006_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car007_shadow"))->setShadowParent(table);
  ((FakeShadow *)root->findByName("Car008_shadow"))->setShadowParent(table);


  // Set menu
  ui = engine.getUI();
  ui->addLabel("FPS");
  ui->addLabel("Drives the red car into the teapot!");
  ui->addLabel("2");
  ui->addLabel("3");
 
  ui->addLabel("[F1] - Show/Hide Menu");
  ui->addLabel("[up/down/left/right] - move the active car");
  ui->addLabel("[r] - reset");
  ui->addLabel("");
  ui->addLabel("");
  ui->addLabel("");
  ui->addLabel("");
  ui->addLabel("");
  

  // Prepare the game
  Node* grid = root->findByName("Grid");
  Node* car001 = grid->findByName("Car001");
  Node* car002 = grid->findByName("Car002");
  Node* car003 = grid->findByName("Car003");
  Node* car004 = grid->findByName("Car004");
  Node* car005 = grid->findByName("Car005");
  Node* car006 = grid->findByName("Car006");
  Node* car007 = grid->findByName("Car007");
  Node* car008 = grid->findByName("Car008");

  Node* teaPot = root->findByName("Teapot");
  Node* brokenTeaPot = root->findByName("BrokenTeaPot");

  
  std::vector<Node*> cars{car001, car002, car003, car004, car005, car006, car007, car008};

  std::vector<std::vector<int>> originalCarPosition = {
      {3,  2,  2,  6,  6,  6},
      {3, -1, -1, -1, -1, -1},
      {0,  0, -1, -1, -1,  1},
	  {5, -1, -1, -1, -1,  1},
	  {5,  4,  4,  7,  7,  7},
	  {5, -1, -1, -1, -1, -1}
   };

  game = new Game(cars, originalCarPosition, teaPot, brokenTeaPot);
  game->setMovementSpeed(0.5f);


  while (isActive) {
    engine.begin();
  }

  engine.free();

  // Done:
  std::cout << "\n[application terminated]" << std::endl;
  return 0;
}
