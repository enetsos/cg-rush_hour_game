#pragma once
#ifndef OVO_READER
#define OVO_RAEDER

#include "motor.h"
#include "material.h"
#include "node.h"
#include "mesh.h"
#include "light.h"
#include "OvObject.h"
#include "OvMesh.h"
#include "OvLight.h"


#include <sstream>
#include <string>
#include <fstream>


class LIB_API OvoReader {
public:
    OvoReader();
    bool loadFromFile(const string& filename);

    // Getters for the loaded data
    const vector<Node>& getNodes() const;
    const vector<Mesh>& getMeshes() const;
    const vector<Material>& getMaterials() const;
    const vector<Light>& getLights() const;

private:
    vector<Node> nodes;
    vector<Mesh> meshes;
    vector<Material> materials;
    vector<Light> lights;

    unsigned int chunkId;
    unsigned int chunkSize;

    void processObjectChunk(const char* data, size_t& position);
    void processNodeChunk(const char* data, size_t& position);
    void processMaterialChunk(const char* data, size_t& position);
    void processMeshChunk(const char* data, size_t& position);
    void processLightChunk(const char* data, size_t& position);
    void processBoneChunk(const char* data, size_t& position);

    glm::mat4 readMatrix(const char* data, size_t& position);
    glm::vec3 readVector3(const char* data, size_t& position);
    // Additional utility methods as needed...
};
#endif // OVO_READER
