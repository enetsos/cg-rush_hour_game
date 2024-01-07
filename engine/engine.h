#include "DirectionalLight.h"
#include "FakeShadow.h"
#include "FileReader.h"
#include "FrameRate.h"
#include "KeyCodes.h"
#include "LibDef.h"
#include "List.h"
#include "OrthogonalProjection.h"
#include "PerspectiveProjection.h"
#include "PointLight.h"
#include "Projection.h"
#include "SpotLight.h"
#include "Texture.h"
#include "UIProjection.h"
#include "Vertex.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "node.h"

/////////////
// CLASSES //
/////////////

/**
 * @class Engine
 * @brief The main engine class responsible for initializing and managing the 3D graphics environment.
 *
 * This class encapsulates functionalities for initializing the rendering environment,
 * handling input, managing scenes, and controlling the render loop. It acts as a central
 * hub for the graphics application.
 */
class LIB_API Engine {
public:
    /**
     * @brief Constructor for the Engine class.
     *
     * Initializes a new instance of the Engine class.
     */
    Engine() {}

    /**
     * @brief Destructor for the Engine class.
     *
     * Cleans up resources used by the Engine instance.
     */
    ~Engine() {}

public:
    /**
     * @brief Initializes the graphics environment with specified parameters.
     *
     * Sets up the rendering window, input callbacks, and other necessary elements
     * for the graphics environment.
     *
     * @param windowName The name of the window to be created.
     * @param keyboardCallbackApplication Pointer to the function handling keyboard inputs.
     * @param displayCallBackApplication Pointer to the function for rendering callbacks.
     */
    void init(const char* windowName, void (*keyboardCallbackApplication)(int),
        void (*displayCallBackApplication)());

    /**
     * @brief Frees up resources allocated by the engine.
     *
     * This method should be called before exiting the application to ensure
     * proper cleanup of resources.
     */
    void free();

    /**
     * @brief Loads a scene from the specified file.
     *
     * @param fileName The name of the file containing the scene data.
     * @return A pointer to the root node of the loaded scene.
     */
    Node* loadScene(std::string fileName);

    /**
     * @brief Clears the screen with the specified color.
     *
     * @param color A glm::vec4 color to clear the screen with.
     */
    void clean(glm::vec4 color);

    /**
     * @brief Prepares the rendering environment for a new frame.
     *
     * This method should be called at the beginning of each frame's rendering.
     */
    void begin();

    /**
     * @brief Swaps the front and back buffers.
     *
     * This static method is typically called after rendering a frame to display
     * it on the screen.
     */
    static void swap();

    /**
     * @brief Forces a refresh of the display.
     *
     * This method can be used to request a redraw of the window contents.
     */
    static void forceRefresh();

    /**
     * @brief Retrieves the current list of elements in the engine.
     *
     * @return A List object representing the current elements.
     */
    static List getList();

    /**
     * @brief Gets the UI projection used by the engine.
     *
     * @return A pointer to the UIProjection instance.
     */
    static UIProjection* getUI();

    /**
     * @brief Gets the current frames per second (FPS) rate.
     *
     * @return An integer representing the current FPS.
     */
    static int getFps();

    /**
     * @brief Sets the path for texture resources.
     *
     * @param width The path to the directory containing texture resources.
     */
    static void setTexturePath(std::string width);

    /**
     * @brief Sets the camera to be used by the engine.
     *
     * @param camera A pointer to the Camera object to be used.
     */
    void setCamera(Camera* camera);

private:
    static void keyboardCallbackDelegator(unsigned char key, int x, int y);
    static void specialCallbackDelegator(int code, int x, int y);
    static void (*keyboardCallbackApplication)(int);

private:
    static void reshapeCallback(int width, int heigth);
    static void displayCallbackDelegator();
    static void (*displayCallBackApplication)();

private:
    static int windowId;
    static Camera* camera;
    static UIProjection* ui;
    static Node* root;
    static List list;
    static FrameRate* fps;
};
