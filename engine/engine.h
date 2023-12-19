#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include "motor.h"
#include "light.h"
#include "mesh.h"
#include "camera.h"
#include "material.h"

//#include "mesh.h"
/////////////
// VERSION //
/////////////

// Generic info:
#define LIB_NAME      "Game Engine v0.1"  ///< Library credits
#define LIB_VERSION   10                              ///< Library version (divide by 10)

using namespace std;


class LIB_API Engine {
public:

	/**
	 * Engine should not be cloneable.
	 */
	Engine(Engine& other) = delete;
	/**
	 * Engine should not be assignable.
	 */
	void operator=(const Engine&) = delete;

	/**
	 * Get the existing engine istance if present, otherwise creates a new one.
	 */
	static Engine* GetInstance();
	void init(const char* title, int width, int height, int argc, char* argv[]);
	void setBackgroundColor(float r, float g, float b);
	bool isRunning();
	void clearWindow();
	void swapBuffers();
	void free();

	void setLightPosition(glm::vec3 position);

protected:
	float angleX, angleY, distance;
	static Engine* engine_;
	bool exe_status;
	void render();


	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void keyboardCallback(unsigned char key, int mouseX, int mouseY);
	static void specialCallback(int key, int mouseX, int mouseY);

	//Mesh* test;
	Engine();
	~Engine();
private:
	glm::vec3 light_position;
};
#endif //ENGINE_H
