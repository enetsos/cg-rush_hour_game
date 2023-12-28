#include "engine.h"
#include <GL/freeglut.h>
#include <cstdio>

// Flags:
bool wireframe = false;
bool flat = false;
bool culling = false;

// Context params:
int windowId;

// Projection matrices:
glm::mat4 perspective;
glm::mat4 ortho;

// Material properties:
Material material;

// list of lights:
Light light(LightType::Point);

// Camera:
Camera camera;

// Window size:
int windowWidth;
int windowHeight;

// FPS:
int fps = 0;
int frames = 0;

// Level of detail:
int detail = 1;

// Static member initialization
Engine *Engine::instance = nullptr;

// Private constructor for Singleton
Engine::Engine() {
  // Initialize member variables
  instance = this;
}

Engine &Engine::getInstance() {
  if (instance == nullptr) {
    instance = new Engine();
  }
  return *instance;
}

void Engine::initialize(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  windowId = glutCreateWindow("3D scene lighting");

  // Global OpenGL settings
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Set up initial states like lighting, materials, etc.
  setupInitialState();

  // Register callback functions
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutKeyboardFunc(keyboardCallback);
  glutSpecialFunc(specialCallback);
  glutTimerFunc(1000, timerCallback, 0);
}

void Engine::run() { glutMainLoop(); }

void Engine::displayCallback() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(camera.getProjectionMatrix()));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  light.render();

  // Set material properties:
  material.apply();

  // Position and render the grid:
  glm::mat4 transGrid =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, -50.0f));
  glLoadMatrixf(glm::value_ptr(transGrid));
  drawGrid(100.0f, (int)pow(8, detail));

  // Position and render the sphere:
  glm::mat4 transSphere =
      glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -60.0f));
  glLoadMatrixf(glm::value_ptr(transSphere));
  glutSolidSphere(6.0, (int)pow(4, detail), (int)pow(4, detail));

  // Position and render the teapot:
  glm::mat4 transTeapot =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -50.0f));
  glLoadMatrixf(glm::value_ptr(transTeapot));
  glFrontFace(GL_CW); // The teapot model uses a different convention
  glutSolidTeapot(6.0);
  glFrontFace(GL_CCW);

  // Position and render the donut:
  glm::mat4 transTorus =
      glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, -3.0f, -30.0f));
  glLoadMatrixf(glm::value_ptr(transTorus));
  glutSolidTorus(1.0, 3.0, (int)pow(4, detail), (int)pow(4, detail));

  //////////////////////////
  // Switch to 2D rendering:

  // Set orthographic projection:
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(instance->ortho));
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

  // Disable lighting before rendering 2D text:
  glDisable(GL_LIGHTING);

  // Write some text:
  char text[64];
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos2f(1.0f, 2.0f);
  glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

  glRasterPos2f(1.0f, 14.0f);
  glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char *)text);

  // Reactivate lighting:
  glEnable(GL_LIGHTING);

  // Swap this context's buffer:
  frames++;
  glutSwapBuffers();
}

void Engine::reshapeCallback(int width, int height) {
  glViewport(0, 0, width, height);
  camera.setProjection(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time a standard keyboard key is pressed.
 * @param key key pressed id
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void Engine::keyboardCallback(unsigned char key, int mouseX, int mouseY) {
  glm::vec4 materialDiffuse;
  switch (key) {
  case 'c':
    culling = !culling;
    if (culling)
      glEnable(GL_CULL_FACE);
    else
      glDisable(GL_CULL_FACE);
    break;

  case 'r':
    materialDiffuse = glm::vec4((rand() % 100) / 100.0f);
    material.setDiffuse(materialDiffuse);
    material.setAmbient(materialDiffuse);
    material.setSpecular(materialDiffuse);
    material.setShininess((float)(rand() % 128));
    break;

  case 'w':
    wireframe = !wireframe;
    if (wireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;

  case 'm':
    if (detail < 3)
      detail++;
    break;

  case 'l':
    if (detail > 1)
      detail--;
    break;

  case 'f':
    flat = !flat;
    if (flat)
      glShadeModel(GL_FLAT);
    else
      glShadeModel(GL_SMOOTH);
  }

  // Force rendering refresh:
  glutPostWindowRedisplay(instance->windowId);
}

void Engine::specialCallback(int key, int mouseX, int mouseY) {
  // Special key handling based on your original main.cpp
  // Change box rotation:
  const float speed = 1.0f;
  glm::vec3 pos = light.getPosition();
  switch (key) {
  case GLUT_KEY_F1:
  case GLUT_KEY_F2:
  case GLUT_KEY_F3:
  case GLUT_KEY_F4:
  case GLUT_KEY_F5:
  case GLUT_KEY_F6:
  case GLUT_KEY_F7:
  case GLUT_KEY_F8:
  case GLUT_KEY_F9:
  case GLUT_KEY_F10:

  case GLUT_KEY_UP:

    pos.z -= speed;
    light.setPosition(pos);
    break;

  case GLUT_KEY_DOWN:
    pos.z += speed;
    light.setPosition(pos);
    break;

  case GLUT_KEY_LEFT:
    pos.x -= speed;
    light.setPosition(pos);
    break;

  case GLUT_KEY_RIGHT:
    pos.x += speed;
    light.setPosition(pos);
    break;

  case GLUT_KEY_PAGE_UP:
    pos.y -= speed;
    light.setPosition(pos);
    break;

  case GLUT_KEY_PAGE_DOWN:
    pos.y += speed;
    light.setPosition(pos);
    break;
  }

  // Force rendering refresh:
  glutPostWindowRedisplay(instance->windowId);
}

void Engine::timerCallback(int value) {
  // Timer event handling based on your original main.cpp
  glutTimerFunc(1000, timerCallback, 0); // Re-register timer callback
}

void Engine::setupInitialState() {
  // Get the window dimensions after creating the window
  windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

  material.setAmbient(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  material.setDiffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  material.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  material.setShininess(128.0f);

  camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f)); // Example position
  camera.setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));   // Look at origin
  camera.setUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // Up vector
  camera.setProjection(45.0f, (float)windowWidth / (float)windowHeight, 0.1f,
                       100.0f); // Perspective projection
}

void Engine::drawGrid(float size, int tesselation) {
  // Compute starting coordinates and step size:
  float startX = -size / 2.0f;
  float startZ = size / 2.0f;
  float triangleSize = size / (float)tesselation;

  // Normal is just one, set it now:
  glNormal3f(0.0f, 1.0f, 0.0f);

  // Go over XZ and draw triangles:
  for (int curZ = 0; curZ < tesselation; curZ++) {
    for (int curX = 0; curX < tesselation; curX++) {
      glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(startX, 0.0f, startZ);
      glVertex3f(startX + triangleSize, 0.0f, startZ);
      glVertex3f(startX, 0.0f, startZ - triangleSize);
      glVertex3f(startX + triangleSize, 0.0f, startZ - triangleSize);
      glEnd();

      startX += triangleSize;
    }
    startX = -size / 2.0f;
    startZ -= triangleSize;
  }
}
