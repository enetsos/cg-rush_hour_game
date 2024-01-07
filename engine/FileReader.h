#include "Vertex.h"
#include "material.h"
#include "node.h"
#include <map>
#include <string>

#ifndef FILEREADER
#define FILEREADER

/**
 * @class FileReader
 * @brief Handles the reading and loading of files into the 3D graphics environment.
 *
 * This class is responsible for reading files from the filesystem and interpreting
 * them to create and configure nodes, materials, and other components necessary
 * for rendering a scene in a 3D graphics environment.
 */
class LIB_API FileReader {
public:
    /**
     * @brief Constructor for the FileReader class.
     *
     * Initializes a new instance of the FileReader class.
     */
    FileReader();

    /**
     * @brief Destructor for the FileReader class.
     *
     * Cleans up resources used by the FileReader instance, like allocated memory for materials
     * and vertices.
     */
    ~FileReader();

public:
    /**
     * @brief Reads a file from the specified path and creates a scene graph.
     *
     * This method opens and interprets a file, constructing a hierarchical scene graph
     * of nodes based on the contents of the file.
     *
     * @param path A constant character pointer to the file path.
     * @return A pointer to the root node of the loaded scene graph.
     */
    Node* readFile(const char* path);

private:
    /**
     * @brief Recursively loads data from the file to construct the scene graph.
     *
     * This method is used internally by readFile to recursively process file data
     * and construct individual nodes in the scene graph.
     *
     * @param dat A FILE pointer to the currently open file.
     * @return A pointer to a Node that represents part of the scene graph.
     */
    Node* recursiveLoad(FILE* dat);

private:
    std::map<std::string, Material*> materials; ///< A map storing materials referenced in the file.
    std::vector<Vertex*> tempVertices; ///< A temporary storage for vertices before they are associated with a node.
};

#endif // FILEREADER
