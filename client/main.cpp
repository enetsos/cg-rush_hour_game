//////////////
// #INCLUDE //
//////////////

// Library header:
#include "engine.h"

// C/C++:
#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include <iostream>
#include <iterator>
#include <vector>

//////////
// MAIN //
//////////

Engine engine;
UIProjection *ui;

float cameraX = 0.0f;
float cameraY = 20.0f;
float cameraZ = 50.0f;
float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;
float cameraSpeed = 2.0f;
float rotationSpeed = 2.0f;

float stationaryCameraX = -102.0f;
float stationaryCameraY = 91.0f;
float stationaryCameraZ = 136;
float stationaryRotationX = -22.0f;
float stationaryRotationY = -26.0f;
float stationaryRotationZ = -8.0f;

Node *root;
bool isActive = true;
bool showUI = true;

Camera *freeCamera = nullptr;
Camera *stationaryCamera = nullptr;
Camera *activeCamera = nullptr;

void keyboardCallback(int key) {

  if (activeCamera == freeCamera) {
    switch (key) {
      // Free camera movement
    case 'w':
      cameraZ--;
      break;
    case 's':
      cameraZ++;
      break;
    case 'a':
      cameraX--;
      break;
    case 'd':
      cameraX++;
      break;
    case 'e':
      cameraY++;
      break;
    case 'q':
      cameraY--;
      break;

      // Free camera rotation
    case '8':
      rotationX++;
      break;
    case '2':
      rotationX--;
      break;
    case '6':
      rotationY--;
      break;
    case '4':
      rotationY++;
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

    // Application controls
  case '.':
    isActive = false;
    break;
  case KEY_F1:
    showUI = !showUI;
    break;

    // Robot arm controls
  case '+':
    break;
  case '-':
    break;
  case KEY_UP:
    break;
  case KEY_DOWN:
    break;
  case KEY_RIGHT:
    break;
  case KEY_LEFT:
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

  // draw scene
  engine.getList().render(activeCamera->getInverse());

  if (showUI) {
    ui->editLabel(0, "FPS: " + std::to_string(engine.getFps()));
    ui->editLabel(2, "[+/-] - Switch active joint: ");
    ui->editLabel(
        7, "[c] - change camera: " +
               std::string(activeCamera == freeCamera ? "free" : "stationary"));
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
  engine.init("RobotArm", keyboardCallback, displayCallback);
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
  ((FakeShadow *)root->findByName("TV_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("arm1_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("arm2_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("arm3_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("clawSupport_shadow"))
      ->setShadowParent(floor);
  ((FakeShadow *)root->findByName("clawL_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("clawR_shadow"))->setShadowParent(floor);
  ((FakeShadow *)root->findByName("Sphere_shadow"))->setShadowParent(floor);

  // Set menu
  ui = engine.getUI();
  ui->addLabel("FPS");
  ui->addLabel("[F1] - Show/Hide Menu");
  ui->addLabel("[+/-]");
  ui->addLabel("[up/down/left/right] - rotate robot joint");
  ui->addLabel("[space] - grab ball");
  ui->addLabel("[w/a/s/d] - move camera");
  ui->addLabel("[8/4/2/6] - rotate camera");
  ui->addLabel("[c]");

  // Prepare robotarm
  Node *ball = root->findByName("Sphere");
  Node *plane = floor->findByName("base");
  Node *joint0 = plane->findByName("arm1");
  Node *joint1 = joint0->findByName("arm2");
  Node *joint2 = joint1->findByName("arm3");
  Node *joint3 = joint2->findByName("clawSupport");
  std::vector<Node *> joints{joint0, joint1, joint2, joint3};
  std::vector<glm::vec3> limits{
      glm::vec3(0.0f, 360.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f),
      glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)};

  while (isActive) {
    engine.begin();
  }

  engine.free();

  // Done:
  std::cout << "\n[application terminated]" << std::endl;
  return 0;
}
