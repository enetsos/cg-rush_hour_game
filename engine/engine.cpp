#include <iostream>
#include "engine.h"
#include <GL/freeglut.h>
//#include "mesh.h"
//////////////
// DLL MAIN //
//////////////

#ifdef _WINDOWS
#include <Windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* DLL entry point. Avoid to rely on it for easier code portability (Linux doesn't use this method).
* @param instDLL handle
* @param reason reason
* @param _reserved reserved
* @return true on success, false on failure
*/
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
	switch (reason)
	{
		///////////////////////////
	case DLL_PROCESS_ATTACH: //
		break;
		///////////////////////////
	case DLL_PROCESS_DETACH: //
		break;
	}
	// Done:
	return true;
}
#endif


LIB_API Engine* Engine::engine_ = nullptr;

LIB_API Engine* Engine::GetInstance() {
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (engine_ == nullptr) {
		engine_ = new Engine();
	}
	return engine_;
}

void LIB_API Engine::init(const char* title, int width, int height, int argc, char* argv[]) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(width, height);
	glutInit(&argc, argv);

	// Set some optional flags:
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Create the window with a specific title:
	glutCreateWindow(title);

	//set callbacks
	glutDisplayFunc(Engine::displayCallback);
	glutReshapeFunc(Engine::reshapeCallback);
	glutSpecialFunc(Engine::specialCallback);
	glutKeyboardFunc(Engine::keyboardCallback);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	exe_status = true;
	glutMainLoop();
	exe_status = false;
	//Execution done
	return;
}

void LIB_API Engine::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
}

bool LIB_API Engine::isRunning() {
	return exe_status;
}

void LIB_API Engine::clearWindow() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void LIB_API Engine::swapBuffers() {
	glutSwapBuffers();
}

void LIB_API Engine::free() {
	delete engine_;
}

void LIB_API Engine::setLightPosition(glm::vec3 position) {
	light_position = position;
}

void Engine::displayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up camera
	Camera camera;
	camera.set_position(glm::vec3(0.0f, 0.0f, 5.0f));

	// Get view and projection matrices from the camera
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = camera.getProjectionMatrix(800.0f / 600.0f);
	glm::mat4 viewProjection = projection * view;

		
	// Render the mesh
	Mesh m("nome", new Material("material1"));
	m.set_position(glm::vec3(0.0f, 0.0f, 0.0f)); // Set mesh position
	m.set_rotation(45.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // Set mesh rotation
	m.displayCube(20);

	// Render the light (assuming you have a Light class with a render method)
	Light light("light1");
	light.setLightColor(glm::vec3(1.0f, 1.0f, 1.0f)); // Set light color
	light.setIntensity(1.0f); // Set light intensity
	light.set_position(glm::vec3(2.0f, 2.0f, 2.0f)); // Set light position
	light.render(viewProjection);

	glLoadMatrixf(glm::value_ptr(viewProjection));

	glutSwapBuffers();
	glutPostWindowRedisplay(glutGetWindow());
}

void LIB_API Engine::reshapeCallback(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}
void LIB_API Engine::keyboardCallback(unsigned char key, int mouseX, int mouseY) {
	//stopping warnings,remove those lines when creating this methods
	key++;
	mouseX++;
	mouseY++;
}
void LIB_API Engine::specialCallback(int key, int mouseX, int mouseY) {
	const float speed = 1.0f;
	switch (key) {
	case GLUT_KEY_UP:
		engine_->angleX -= speed;
		break;
	case GLUT_KEY_DOWN:
		engine_->angleX += speed;
		break;
	case GLUT_KEY_LEFT:
		engine_->angleY -= speed;
		break;
	case GLUT_KEY_RIGHT:
		engine_->angleY += speed;
		break;
	}
	//stopping warnings
	mouseX++;
	mouseY++;
}

LIB_API Engine::Engine() :
	angleX{ 0.0f },
	angleY{ 0.0f },
	distance{ -45.0f },
	exe_status{ false }
{}

LIB_API Engine::~Engine() {
}

