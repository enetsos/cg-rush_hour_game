#include "ovoReader.h"


OvoReader::OvoReader() {}

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
            case OvObject::Type::MESH:
                processMeshChunk(data.data(), position);
                break;
              case OvObject::Type::SKINNED:
				  processMeshChunk(data.data(), position);
					break;
                    case OvObject::Type::LIGHT:
				processLightChunk(data.data(), position);
				break;

            // ... handle other cases
        default:
            std::cerr << "Unknown chunk type: " << chunkId << std::endl;
            break;
        }
    }


    return true;
}

void OvoReader::printData() const{
    std::cout << "Nodes:\n";
    for (const auto& node : nodes) {
        node.printData();
    }

    std::cout << "\nMeshes:\n";
    for (const auto& mesh : meshes) {
        mesh.printData();
    }

    std::cout << "\nMaterials:\n";
    for (const auto& material : materials) {
        material.printData();
    }

    std::cout << "\nLights:\n";
    for (const auto& light : lights) {
        light.printData();
    }

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

    std::string nodeName = readString(data, position);
    
    glm::mat4 matrix;
    memcpy(&matrix, data + position, sizeof(glm::mat4));
    position += sizeof(glm::mat4);

    unsigned int children;
    memcpy(&children, data + position, sizeof(unsigned int));
   
    position += sizeof(unsigned int);

    std::string targetName = readString(data, position);
    
    Node node(nodeName, matrix, children, targetName);
     nodes.push_back(node);

}

void OvoReader::processMaterialChunk(const char* data, size_t& position) {

    // Material name:
    std::string materialName = readString(data, position);

    // Material term colors, starting with emissive:
    glm::vec3 emission, albedo;
    memcpy(&emission, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Albedo:
    memcpy(&albedo, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

    // Roughness factor:
    float roughness;
    memcpy(&roughness, data + position, sizeof(float));
    position += sizeof(float);

    // Metalness factor:
    float metalness;
    memcpy(&metalness, data + position, sizeof(float));
    position += sizeof(float);

    // Transparency factor:
    float alpha;
    memcpy(&alpha, data + position, sizeof(float));
    position += sizeof(float);

    // Texture filenames:
    std::string textureName = readString(data, position);

    std::string normalMapName = readString(data, position);

    std::string heightMapName = readString(data, position);

    std::string roughnessMapName = readString(data, position);

    std::string metalnessMapName = readString(data, position);
    
    Material material(materialName,
        emission,
        albedo,
        roughness,
        metalness,
        alpha,
        textureName,
        normalMapName,
        heightMapName,
        roughnessMapName,
        metalnessMapName
    );

    
    materials.push_back(material);

}
void OvoReader::processMeshChunk(const char* data, size_t& position) {
    PhysProps mp;
    //vector of hulls
    vector<Hull> hulls;
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
    position += sizeof(unsigned char);

    // Material name, or [none] if not used:
    std::string materialName = readString(data, position);

    // Mesh bounding sphere radius and box corners:
    float radius;
    memcpy(&radius, data + position, sizeof(float));
    position += sizeof(float);

    glm::vec3 bBoxMin, bBoxMax;
    memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);
    memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);

        // Optional physics properties:
        unsigned char hasPhysics;
        memcpy(&hasPhysics, data + position, sizeof(unsigned char));
        position += sizeof(unsigned char);
        if (hasPhysics)
        {
            
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
                    Hull hull;
                    

                    // Hull number of vertices:
                    unsigned int nrOfVertices;
                    memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    // Hull number of faces:
                    unsigned int nrOfFaces;
                    memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
                    position += sizeof(unsigned int);

                    
                    memcpy(&hull.centroid, data + position, sizeof(glm::vec3));
                    position += sizeof(glm::vec3);

                    // Iterate through hull vertices:
                    for (unsigned int c = 0; c < nrOfVertices; c++)
                    {
                        
                        memcpy(&hull.vertices, data + position, sizeof(glm::vec3));
                        position += sizeof(glm::vec3);
                    }

                    // Iterate through hull faces:
                    for (unsigned int c = 0; c < nrOfFaces; c++)
                    {
                        
                        memcpy(hull.faces, data + position, sizeof(unsigned int) * 3);
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

        //vector of LODs
        vector<LOD> lods;

        // For each LOD...:
        vector<unsigned int> verticesPerLOD(LODs); // Let's store this information for the skinned part, in case
        for (unsigned int l = 0; l < LODs; l++)
        {
            LOD lod;
            cout << "      LOD . . :  " << l + 1 << "/" << LODs << endl;

            
            memcpy(&lod.numVertices, data + position, sizeof(unsigned int));
            cout << "   Nr. vertices  :  " << lod.numVertices << endl;
            position += sizeof(unsigned int);
            verticesPerLOD[l] = lod.numVertices;

            // ...and faces:
            memcpy(&lod.numFaces, data + position, sizeof(unsigned int));
            cout << "   Nr. faces . . :  " << lod.numFaces << endl;
            position += sizeof(unsigned int);

            // Interleaved and compressed vertex/normal/UV/tangent data:                    
            for (unsigned int c = 0; c < lod.numVertices; c++)
            {
                
               
                memcpy(&lod.vertices, data + position, sizeof(glm::vec3));
               position += sizeof(glm::vec3);

                
                memcpy(&lod.normals, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);

                
                memcpy(&lod.textureCoords, data + position, sizeof(unsigned int));
               position += sizeof(unsigned int);

                
                memcpy(&lod.tangents, data + position, sizeof(unsigned int));
                position += sizeof(unsigned int);
            }

            // Faces:
            for (unsigned int c = 0; c < lod.numFaces; c++)
            {
                
                memcpy(lod.faces, data + position, sizeof(unsigned int) * 3);
                position += sizeof(unsigned int) * 3;
            }
            lods.push_back(lod);
        }

        vector<Bone> bones;
        // Extra information for skinned meshes:
        if (isSkinned)
        {
            Bone bone;
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
                bone.boneName = readString(data, position);

               // Bone matrix:
                memcpy(&bone.boneMatrix, data + position, sizeof(glm::mat4));
                position += sizeof(glm::mat4);
            }

            // For each LOD...:
            for (unsigned int l = 0; l < LODs; l++)
            {

                // Per vertex bone weights and indexes:               
                for (unsigned int c = 0; c < verticesPerLOD[l]; c++)
                {
                    
                    // Bone indexes:                    
                    memcpy(bone.boneIndex, data + position, sizeof(unsigned int) * 4);
                    position += sizeof(unsigned int) * 4;

                    // Bone weights:                    
                    memcpy(bone.boneWeightData, data + position, sizeof(unsigned short) * 4);
                   
                    position += sizeof(unsigned short) * 4;
                }
            }

            bones.push_back(bone);

            SkinnedMesh skinnedMesh(meshName, matrix, children, targetName,
                				subtypeName, materialName, radius, bBoxMin, bBoxMax, hasPhysics, mp, hulls, lods, poseMatrix, bones);
        
            meshes.push_back(skinnedMesh);
        }
        else
        {
            Mesh mesh(meshName, matrix, children, targetName,
                isSkinned, subtypeName, materialName, radius, bBoxMin, bBoxMax, hasPhysics, mp, hulls, lods);
            meshes.push_back(mesh);
        }
    
}

void OvoReader::processLightChunk(const char* data, size_t& position) {

        // Light name:
        std::string lightName = readString(data, position);

        // Light matrix:
        glm::mat4 matrix;
        memcpy(&matrix, data + position, sizeof(glm::mat4));
        position += sizeof(glm::mat4);

        // Nr. of children nodes:
        unsigned int children;
        memcpy(&children, data + position, sizeof(unsigned int));
        position += sizeof(unsigned int);

        // Optional target node name, or [none] if not used:
        std::string targetName = readString(data, position);

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

       

        Light light(lightName, matrix, children, targetName,
            			subtypeName, color, direction,
            			radius, cutoff, spotExponent, castShadows, isVolumetric);

        lights.push_back(light);
}




