#include "LibDef.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <string>

#ifndef OBJECT
#define OBJECT

class LIB_API Object {

public:
  Object() : id(Object::getNextId()) {}
  Object(int id, const std::string name);
  ~Object();

public:
  int getId() const;
  std::string getName() const;
  void setName(const std::string name);
  static int getNextId();
  virtual void render(glm::mat4 cameraInv);

private:
  static int nextId;
  const int id;
  std::string name;
};

#endif // OBJECT
