#include "ovoReader.h"

// Helper function to read a string from the data buffer
std::string readString(const char*& data, size_t& position) {
    std::string result(data + position); // Constructs string up to the null character
    position += result.size() + 1; // Move past the string and the null terminator
    return result;
}

bool OvoReader::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }

    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&chunkId), sizeof(chunkId));
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));

        if (file.eof()) break;

        std::vector<char> data(chunkSize);
        file.read(data.data(), chunkSize);

        size_t position = 0;
        switch (static_cast<OvObject::Type>(chunkId)) {
        case OvObject::Type::OBJECT:
            processObjectChunk(data.data(), position);
            break;
        case OvObject::Type::NODE:
            processNodeChunk(data.data(), position);
            break;
        case OvObject::Type::MATERIAL:
            processMaterialChunk(data.data(), position);
            break;
            // ... handle other cases
        default:
            std::cerr << "Unknown chunk type: " << chunkId << std::endl;
            break;
        }
    }


    return true;
}

void OvoReader::processObjectChunk(const char* data, size_t& position) {
    // Implementation for processing the OBJECT chunk
    cout << "version]" << endl;

    // OVO revision number:
    unsigned int versionId;
    memcpy(&versionId, data + position, sizeof(unsigned int));
    cout << "   Version . . . :  " << versionId << endl;
    position += sizeof(unsigned int);
}

void OvoReader::processNodeChunk(const char* data, size_t& position) {
    cout << "node]" << endl;

    std::string nodeName = readString(data, position);
    cout << "   Name  . . . . :  " << nodeName << endl;

    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    cout << "   Nr. children  :  " << children << endl;
    position += sizeof(unsigned int);

    std::string targetName = readString(data, position);
    cout << "   Target node . :  " << targetName << endl;
    
}

void OvoReader::processMaterialChunk(const char* data, size_t& position) {
    cout << "material]" << endl;

    // Material name:
    std::string materialName = readString(data, position);
    cout << "   Name  . . . . :  " << materialName << endl;

    // Material term colors, starting with emissive:
    glm::vec3 emission, albedo;
    memcpy(&emission, data + position, sizeof(glm::vec3));
    cout << "   Emission  . . :  " << emission.r << ", " << emission.g << ", " << emission.b << endl;
    position += sizeof(glm::vec3);

    // Albedo:
    memcpy(&albedo, data + position, sizeof(glm::vec3));
    cout << "   Albedo  . . . :  " << albedo.r << ", " << albedo.g << ", " << albedo.b << endl;
    position += sizeof(glm::vec3);

    // Roughness factor:
    float roughness;
    memcpy(&roughness, data + position, sizeof(float));
    cout << "   Roughness . . :  " << roughness << endl;
    position += sizeof(float);

    // Metalness factor:
    float metalness;
    memcpy(&metalness, data + position, sizeof(float));
    cout << "   Metalness . . :  " << metalness << endl;
    position += sizeof(float);

    // Transparency factor:
    float alpha;
    memcpy(&alpha, data + position, sizeof(float));
    cout << "   Transparency  :  " << alpha << endl;
    position += sizeof(float);

    // Texture filenames:
    std::string textureName = readString(data, position);
    cout << "   Albedo tex. . :  " << textureName << endl;

    std::string normalMapName = readString(data, position);
    cout << "   Normalmap tex.:  " << normalMapName << endl;

    std::string heightMapName = readString(data, position);
    cout << "   Heightmap tex.:  " << heightMapName << endl;

    std::string roughnessMapName = readString(data, position);
    cout << "   Roughness tex.:  " << roughnessMapName << endl;

    std::string metalnessMapName = readString(data, position);
    cout << "   Metalness tex.:  " << metalnessMapName << endl;
}
void OvoReader::processMeshChunk(const char* data, size_t& position) {
    bool isSkinned = false;
    if ((OvObject::Type)chunkId == OvObject::Type::SKINNED) {
        isSkinned = true;
        cout << "skinned mesh]" << endl;
    }
    else {
        cout << "mesh]" << endl;
    }

    // Mesh name:
    std::string meshName = readString(data, position);
    cout << "   Name  . . . . :  " << meshName << endl;

    // Mesh matrix:
    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    // Mesh nr. of children nodes:
    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
    cout << "   Nr. children  :  " << children << endl;
    position += sizeof(unsigned int);

    // Optional target node, or [none] if not used:
    std::string targetName = readString(data, position);
    cout << "   Target node . :  " << targetName << endl;

    // Mesh subtype (see OvMesh SUBTYPE enum):
    unsigned char subtype;
    memcpy(&subtype, data + position, sizeof(unsigned char));
    std::string subtypeName;
    switch ((OvMesh::Subtype)subtype) {
    case OvMesh::Subtype::DEFAULT: subtypeName = "standard"; break;
    case OvMesh::Subtype::NORMALMAPPED: subtypeName = "normal-mapped"; break;
    case OvMesh::Subtype::TESSELLATED: subtypeName = "tessellated"; break;
    default: subtypeName = "UNDEFINED"; break;
    }
    cout << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << endl;
    position += sizeof(unsigned char);

    // Material name, or [none] if not used:
    std::string materialName = readString(data, position);
    cout << "   Material  . . :  " << materialName << endl;

    // Mesh bounding sphere radius and box corners:
    float radius;
    memcpy(&radius, data + position, sizeof(float));
    cout << "   Radius  . . . :  " << radius << endl;
    position += sizeof(float);

    glm::vec3 bBoxMin, bBoxMax;
    memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);
    memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);
    cout << "   BBox minimum  :  " << bBoxMin.x << ", " << bBoxMin.y << ", " << bBoxMin.z << endl;
    cout << "   BBox maximum  :  " << bBoxMax.x << ", " << bBoxMax.y << ", " << bBoxMax.z << endl;

        // Optional physics properties:
        unsigned char hasPhysics;
        memcpy(&hasPhysics, data + position, sizeof(unsigned char));
        cout << "   Physics . . . :  " << (int)hasPhysics << endl;
        position += sizeof(unsigned char);
        if (hasPhysics)
        {
            /**
             * Mesh physics properties.
             */
            struct PhysProps
            {
                // Pay attention to 16 byte alignement (use padding):      
                unsigned char type;
                unsigned char contCollisionDetection;
                unsigned char collideWithRBodies;
                unsigned char hullType;

                // Vector data:
                glm::vec3 massCenter;

                // Mesh properties:
                float mass;
                float staticFriction;
                float dynamicFriction;
                float bounciness;
                float linearDamping;
                float angularDamping;
                unsigned int nrOfHulls;
                unsigned int _pad;

                // Pointers:
                void* physObj;
                void* hull;
            };

            PhysProps mp;
            memcpy(&mp, data + position, sizeof(PhysProps));
            position += sizeof(PhysProps);
            cout << "      Type . . . :  " << (int)mp.type << endl;
            cout << "      Hull type  :  " << (int)mp.hullType << endl;
            cout << "      Cont. coll.:  " << (int)mp.contCollisionDetection << endl;
            cout << "      Col. bodies:  " << (int)mp.collideWithRBodies << endl;
            cout << "      Center . . :  " << mp.massCenter.x << ", " << mp.massCenter.y << ", " << mp.massCenter.z << endl;
            cout << "      Mass . . . :  " << mp.mass << endl;
            cout << "      Static . . :  " << mp.staticFriction << endl;
            cout << "      Dynamic  . :  " << mp.dynamicFriction << endl;
            cout << "      Bounciness :  " << mp.bounciness << endl;
            cout << "      Linear . . :  " << mp.linearDamping << endl;
            cout << "      Angular  . :  " << mp.angularDamping << endl;
            cout << "      Nr. hulls  :  " << mp.nrOfHulls << endl;

            // Custom hull(s) used?
            if (mp.nrOfHulls)
            {
                for (unsigned int c = 0; c < mp.nrOfHulls; c++)
                {
                    

                    // Hull number of vertices:
                    unsigned int nrOfVertices;
                    memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    // Hull number of faces:
                    unsigned int nrOfFaces;
                    memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    // Hull centroid:
                    glm::vec3 centroid;
                    memcpy(&centroid, data + position, sizeof(glm::vec3));
                    position += sizeof(glm::vec3);

                    // Iterate through hull vertices:
                    for (unsigned int c = 0; c < nrOfVertices; c++)
                    {
                        // Vertex coords:    
                        glm::vec3 vertex;
                        memcpy(&vertex, data + position, sizeof(glm::vec3));
                        position += sizeof(glm::vec3);
                    }

                    // Iterate through hull faces:
                    for (unsigned int c = 0; c < nrOfFaces; c++)
                    {
                        unsigned int face[3];
                        memcpy(face, data + position, sizeof(unsigned int) * 3);
                        position += sizeof(unsigned int) * 3;
                    }
                }
            }
        }

        // Nr. of LODs:
        unsigned int LODs;
        memcpy(&LODs, data + position, sizeof(unsigned int));
        cout << "   Nr. of LODs   :  " << LODs << endl;
        position += sizeof(unsigned int);

        // For each LOD...:
        vector<unsigned int> verticesPerLOD(LODs); // Let's store this information for the skinned part, in case
        for (unsigned int l = 0; l < LODs; l++)
        {
            cout << "      LOD . . :  " << l + 1 << "/" << LODs << endl;

            // Nr. of vertices:
            unsigned int vertices, faces;
            memcpy(&vertices, data + position, sizeof(unsigned int));
            cout << "   Nr. vertices  :  " << vertices << endl;
            position += sizeof(unsigned int);
            verticesPerLOD[l] = vertices;

            // ...and faces:
            memcpy(&faces, data + position, sizeof(unsigned int));
            cout << "   Nr. faces . . :  " << faces << endl;
            position += sizeof(unsigned int);

            // Interleaved and compressed vertex/normal/UV/tangent data:                    
            for (unsigned int c = 0; c < vertices; c++)
            {
                
                // Vertex coords:    
                glm::vec3 vertex;
                memcpy(&vertex, data + position, sizeof(glm::vec3));
               position += sizeof(glm::vec3);

                // Vertex normal:
                unsigned int normalData;
                memcpy(&normalData, data + position, sizeof(unsigned int));
                
                position += sizeof(unsigned int);

                // Texture coordinates:
                unsigned int textureData;
                memcpy(&textureData, data + position, sizeof(unsigned int));
               
                position += sizeof(unsigned int);

                // Tangent vector:
                unsigned int tangentData;
                memcpy(&tangentData, data + position, sizeof(unsigned int));
                
                position += sizeof(unsigned int);
            }

            // Faces:
            for (unsigned int c = 0; c < faces; c++)
            {
                // Face indexes:
                unsigned int face[3];
                memcpy(face, data + position, sizeof(unsigned int) * 3);
                position += sizeof(unsigned int) * 3;
            }
        }

        // Extra information for skinned meshes:
        if (isSkinned)
        {
            // Initial mesh pose matrix:               
            glm::mat4 poseMatrix;
            memcpy(&poseMatrix, data + position, sizeof(glm::mat4));
            position += sizeof(glm::vec4);

            // Bone list:
            unsigned int nrOfBones;
            memcpy(&nrOfBones, data + position, sizeof(unsigned int));
            cout << "   Nr. bones . . :  " << nrOfBones << endl;
            position += sizeof(unsigned int);

            // For each bone...:
            for (unsigned int c = 0; c < nrOfBones; c++)
            {
                // Bone name:
                std::string boneName = readString(data, position);
                cout << "      Bone name  :  " << boneName << " (" << c << ")" << endl;

                // Initial bone pose matrix (already inverted):
                glm::mat4 boneMatrix;
                memcpy(&boneMatrix, data + position, sizeof(glm::mat4));
                position += sizeof(glm::mat4);
            }

            // For each LOD...:
            for (unsigned int l = 0; l < LODs; l++)
            {
                cout << "      LOD . . :  " << l + 1 << "/" << LODs << endl;

                // Per vertex bone weights and indexes:               
                for (unsigned int c = 0; c < verticesPerLOD[l]; c++)
                {
                    
                    // Bone indexes:
                    unsigned int boneIndex[4];
                    memcpy(boneIndex, data + position, sizeof(unsigned int) * 4);
                    position += sizeof(unsigned int) * 4;

                    // Bone weights:
                    unsigned short boneWeightData[4];
                    memcpy(boneWeightData, data + position, sizeof(unsigned short) * 4);
                   
                    position += sizeof(unsigned short) * 4;
                }
            }
        }
    
}

void OvoReader::processLightChunk(const char* data, size_t& position) {
        cout << "light]" << endl;

        // Light name:
        std::string lightName = readString(data, position);
        cout << "   Name  . . . . :  " << lightName << endl;

        // Light matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + position, sizeof(glm::mat4));
        position += sizeof(glm::mat4);

        // Nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + position, sizeof(unsigned int));
        cout << "   Nr. children  :  " << children << endl;
        position += sizeof(unsigned int);

        // Optional target node name, or [none] if not used:
        std::string targetName = readString(data, position);
        cout << "   Target node . :  " << targetName << endl;

        // Light subtype (see OvLight SUBTYPE enum):
        unsigned char subtype;
        memcpy(&subtype, data + position, sizeof(unsigned char));
        std::string subtypeName;
        switch ((OvLight::Subtype)subtype) {
        case OvLight::Subtype::DIRECTIONAL: subtypeName = "directional"; break;
        case OvLight::Subtype::OMNI: subtypeName = "omni"; break;
        case OvLight::Subtype::SPOT: subtypeName = "spot"; break;
        default: subtypeName = "UNDEFINED"; break;
        }
        cout << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << endl;
        position += sizeof(unsigned char);

        // Light color, radius, direction, cutoff, and other properties:
        glm::vec3 color, direction;
        float radius, cutoff, spotExponent;
        unsigned char castShadows, isVolumetric;

        memcpy(&color, data + position, sizeof(glm::vec3));
        position += sizeof(glm::vec3);
        memcpy(&radius, data + position, sizeof(float));
        position += sizeof(float);
        memcpy(&direction, data + position, sizeof(glm::vec3));
        position += sizeof(glm::vec3);
        memcpy(&cutoff, data + position, sizeof(float));
        position += sizeof(float);
        memcpy(&spotExponent, data + position, sizeof(float));
        position += sizeof(float);
        memcpy(&castShadows, data + position, sizeof(unsigned char));
        position += sizeof(unsigned char);
        memcpy(&isVolumetric, data + position, sizeof(unsigned char));
        position += sizeof(unsigned char);

        cout << "   Color . . . . :  " << color.r << ", " << color.g << ", " << color.b << endl;
        cout << "   Radius  . . . :  " << radius << endl;
        cout << "   Direction . . :  " << direction.r << ", " << direction.g << ", " << direction.b << endl;
        cout << "   Cutoff  . . . :  " << cutoff << endl;
        cout << "   Spot exponent :  " << spotExponent << endl;
        cout << "   Cast shadows  :  " << static_cast<int>(castShadows) << endl;
        cout << "   Volumetric  . :  " << static_cast<int>(isVolumetric) << endl;
    
}



