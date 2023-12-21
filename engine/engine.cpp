#include "engine.h"
#include <GL/freeglut.h>

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
glm::vec4 materialAmbient(0.5f, 0.5f, 0.5f, 1.0f);
glm::vec4 materialDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
glm::vec4 materialSpecular(1.0f, 1.0f, 1.0f, 1.0f);
float materialShininess = 128.0f;

// Light properties:
glm::vec3 lightPosition(0.0f, -3.0f, -30.0f);
glm::vec4 lightAmbient(0.5f, 0.5f, 0.5f, 1.0f);
glm::vec4 lightDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
glm::vec4 lightSpecular(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightDirection(0.0f, 0.0f, 0.0f);
float lightCutoff = 180.0f;

// FPS:
int fps = 0;
int frames = 0;

// Level of detail:
int detail = 1;

// Static member initialization
Engine* Engine::instance = nullptr;

// Private constructor for Singleton
Engine::Engine() {
    // Initialize member variables
    instance = this;
}

Engine& Engine::getInstance() {
    if (instance == nullptr) {
        instance = new Engine();
    }
    return *instance;
}

void Engine::initialize(int argc, char* argv[]) {
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

void Engine::run() {
    glutMainLoop();
}

void Engine::displayCallback() {
    // Rendering logic from your original main.cpp display logic
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ////////////////
    // 3D rendering:

    // Set perpsective matrix:
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(instance->perspective));
    glMatrixMode(GL_MODELVIEW);

    // Set light position:
    glm::mat4 transLight = glm::translate(glm::mat4(1.0f), lightPosition);
    glLoadMatrixf(glm::value_ptr(transLight));

    // Draw a small emissive sphere to show light position:   
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(1.0f)));
    glutSolidSphere(0.5, 8, 8);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f)));

    // Light position is set to object coordinates and is modified by the current OpenGL matrix (as with any other object):
    glm::vec4 objectCoordPosition(0.0f, 0.0f, 0.0f, 1.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(objectCoordPosition));
    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(lightAmbient));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(lightDiffuse));
    glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(lightSpecular));

    // Set material properties:
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(materialAmbient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(materialDiffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(materialSpecular));

    // Position and render the grid:
    glm::mat4 transGrid = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, -50.0f));
    glLoadMatrixf(glm::value_ptr(transGrid));
    drawGrid(100.0f, (int)pow(8, detail));

    // Position and render the sphere:
    glm::mat4 transSphere = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -60.0f));
    glLoadMatrixf(glm::value_ptr(transSphere));
    glutSolidSphere(6.0, (int)pow(4, detail), (int)pow(4, detail));

    // Position and render the teapot:
    glm::mat4 transTeapot = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -50.0f));
    glLoadMatrixf(glm::value_ptr(transTeapot));
    glFrontFace(GL_CW);  // The teapot model uses a different convention
    glutSolidTeapot(6.0);
    glFrontFace(GL_CCW);

    // Position and render the donut:
    glm::mat4 transTorus = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, -3.0f, -30.0f));
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
    sprintf_s(text, "FPS: %d", fps);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(1.0f, 2.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);

    sprintf_s(text, "LOD: %d", detail);
    glRasterPos2f(1.0f, 14.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);

    // Reactivate lighting:
    glEnable(GL_LIGHTING);

    // Swap this context's buffer:
    frames++;
    glutSwapBuffers();
}

void Engine::reshapeCallback(int width, int height) {
    glViewport(0, 0, width, height);

    // Refresh projection matrices:
    instance->perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
    instance->ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * This callback is invoked each time a standard keyboard key is pressed.
 * @param key key pressed id
 * @param mouseX mouse X coordinate
 * @param mouseY mouse Y coordinate
 */
void Engine::keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
    case 'c':
        culling = !culling;
        if (culling)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        break;

    case 'r':
        materialDiffuse.x = (rand() % 100) / 100.0f;
        materialDiffuse.y = (rand() % 100) / 100.0f;
        materialDiffuse.z = (rand() % 100) / 100.0f;
        materialAmbient = materialDiffuse;
        materialSpecular = materialDiffuse;
        materialShininess = (float)(rand() % 128);
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
    switch (key)
    {
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
        lightDiffuse.x = ((float)(key - GLUT_KEY_F1)) / 10.0f;
        lightDiffuse.y = lightDiffuse.x;
        lightDiffuse.z = lightDiffuse.x;
        lightAmbient = lightDiffuse;
        lightSpecular = lightDiffuse;
        break;

    case GLUT_KEY_UP:
        lightPosition.z -= speed;
        break;

    case GLUT_KEY_DOWN:
        lightPosition.z += speed;
        break;

    case GLUT_KEY_LEFT:
        lightPosition.x -= speed;
        break;

    case GLUT_KEY_RIGHT:
        lightPosition.x += speed;
        break;

    case GLUT_KEY_PAGE_UP:
        lightPosition.y += speed;
        break;

    case GLUT_KEY_PAGE_DOWN:
        lightPosition.y -= speed;
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
    // Set up initial states like lighting, materials, etc.
}

void Engine::drawGrid(float size, int tesselation)
{
    // Compute starting coordinates and step size:
    float startX = -size / 2.0f;
    float startZ = size / 2.0f;
    float triangleSize = size / (float)tesselation;

    // Normal is just one, set it now:
    glNormal3f(0.0f, 1.0f, 0.0f);

    // Go over XZ and draw triangles:
    for (int curZ = 0; curZ < tesselation; curZ++)
    {
        for (int curX = 0; curX < tesselation; curX++)
        {
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

