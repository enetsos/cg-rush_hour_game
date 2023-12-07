#include <iostream>
#include "engine.h"
#include <GL/freeglut.h>
#include "mesh.h"
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

}

void LIB_API Engine::swapBuffers() {
	glutSwapBuffers();
}

void LIB_API Engine::free() {
	delete engine_;
}


//private methods
void LIB_API Engine::displayCallback() {   // Clear the screen:
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//matrix to move shape
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, engine_->distance));
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(engine_->angleX), glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, glm::radians(engine_->angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 f = translation * rotation;
	glLoadMatrixf(glm::value_ptr(f));
	//display mesh
	Mesh m("nome", new Material("material1"));
	m.displayCube(20);
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

