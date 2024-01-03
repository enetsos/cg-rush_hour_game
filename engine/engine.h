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
 * @brief Simple static class example.
 */
class LIB_API Engine {
public:
  Engine() {}
  ~Engine() {}

public:
  // Init/free:
  void init(const char *windowName, void (*keyboardCallbackApplication)(int),
            void (*displayCallBackApplication)());
  void free();

  Node *loadScene(std::string fileName);

  void clean(glm::vec4 color);
  void begin();
  static void swap();
  static void forceRefresh();

  static List getList();
  static UIProjection *getUI();
  static int getFps();
  static void setTexturePath(std::string width);
  void setCamera(Camera *camera);

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
  static Camera *camera;
  static UIProjection *ui;
  static Node *root;
  static List list;
  static FrameRate *fps;
};