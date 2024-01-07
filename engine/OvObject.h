#include "FileReader.h"

/**
 * @class OvObject
 * @brief Represents an object with various types in a graphics or game engine context.
 *
 * This class is a simplified version of OvObject, focusing on enumerating different types of entities
 * that can be represented. It includes an enumeration for foundational types, derived classes, animation,
 * physics-related entities, and a terminator.
 */
class OvObject
{
public:
    /**
     * @enum Type
     * @brief Enumerates the different types of entities in the engine.
     *
     * This enumeration specifies various types of entities, ranging from foundational objects to
     * more complex types like shaders, textures, materials, cameras, lights, meshes, and physics-related objects.
     * It also includes a terminator to mark the end of the enum.
     */
    enum class Type : int  ///< Type of entities
    {
        // Foundation types:
        O_OBJECT = 0,      ///< Basic object type.
        O_NODE,            ///< Node type, a fundamental part of the scene graph.
        O_OBJECT2D,        ///< 2D object type.
        O_OBJECT3D,        ///< 3D object type.
        O_LIST,            ///< List type, for managing collections of objects.

        // Derived classes:
        O_BUFFER,          ///< Buffer type, for handling data buffering.
        O_SHADER,          ///< Shader type, for shader program entities.
        O_TEXTURE,         ///< Texture type, for texture entities.
        O_FILTER,          ///< Filter type, used for graphical filters.
        O_MATERIAL,        ///< Material type, defining surface properties.
        O_FBO,             ///< Framebuffer Object type.
        O_QUAD,            ///< Quad type, a simple rectangle primitive.
        O_BOX,             ///< Box type, a simple 3D box primitive.
        O_SKYBOX,          ///< Skybox type, used for rendering skyboxes.
        O_FONT,            ///< Font type, for rendering text.
        O_CAMERA,          ///< Camera type, for viewing scenes.
        O_LIGHT,           ///< Light type, for scene illumination.
        O_BONE,            ///< Bone type, for skeletal animation.
        O_MESH,	           ///< Mesh type, for 3D geometry.
        O_SKINNED,         ///< Skinned mesh type, for skeletal animated meshes.
        O_INSTANCED,       ///< Instanced type, for instanced rendering.
        O_PIPELINE,        ///< Pipeline type, for rendering pipelines.
        O_EMITTER,         ///< Emitter type, for particle systems.

        // Animation type:
        O_ANIM,            ///< Animation type, for animating objects.

        // Physics related:
        O_PHYSICS,         ///< Physics type, for physics-related entities.

        // Terminator:
        O_LAST,            ///< Terminator for the enumeration.
    };
};
