#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "motor.h"
#include "mesh.h"
#include "node.h"
#include "light.h"
#include "material.h"
#include "camera.h"

class LIB_API Engine {
public:
    // Singleton access
    static Engine& getInstance();

    // Initialize and run the engine
    void initialize(int argc, char* argv[]);
    void run();

private:
    static Engine* instance; // Add this line
    int windowId;            // Add this line for window ID
    glm::mat4 perspective;  // Add this line for the perspective matrix
    glm::mat4 ortho;        // Add this line for the orthographic matrix

    Engine(); // Private constructor for Singleton
    static void displayCallback(); // Display callback for rendering
    static void reshapeCallback(int width, int height); // Window reshape callback
    static void keyboardCallback(unsigned char key, int x, int y); // Keyboard callback
    static void specialCallback(int key, int x, int y); // Special keyboard callback
    static void timerCallback(int value); // Timer callback for animation
    static void setupInitialState();
    static void drawGrid(float size, int tesselation);
    // Other necessary callbacks and private methods

    // Engine state
    Mesh cubeMesh; // Mesh for rendering a cube
};

#endif // ENGINE_H
