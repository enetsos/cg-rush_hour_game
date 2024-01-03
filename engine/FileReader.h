#include "Vertex.h"
#include "material.h"
#include "node.h"
#include <map>
#include <string>

#ifndef FILEREADER
#define FILEREADER

class LIB_API FileReader {
public:
  FileReader();
  ~FileReader();

public:
  Node *readFile(const char *path);

private:
  Node *recursiveLoad(FILE *dat);

private:
  std::map<std::string, Material *> materials;
  std::vector<Vertex *> tempVertices;
};

#endif // FILEREADER
