#pragma once

/**
 * @class OvMesh
 * @brief Represents a mesh object with different subtypes.
 *
 * This class is a simplified version of OvMesh, focusing on the different subtypes of meshes
 * that can be represented. It includes an enumeration for different kinds of meshes,
 * such as Default, NormalMapped, and Tessellated.
 */
class OvMesh
{
public:
    /**
     * @enum Subtype
     * @brief Enumerates the different subtypes of meshes.
     *
     * This enumeration is used to specify the kind of mesh, including foundational types
     * like Default, NormalMapped, and Tessellated meshes. It also includes a 'LAST' value
     * as a terminator for the enumeration.
     */
    enum class Subtype : int ///< Kind of mesh
    {
        DEFAULT = 0,        ///< Represents a default mesh with basic geometry.
        NORMALMAPPED,       ///< Represents a mesh enhanced with normal mapping for more detailed surface textures.
        TESSELLATED,        ///< Represents a tessellated mesh, allowing for dynamically detailed geometry.

        LAST,               ///< Terminator for the enumeration, used to mark the end of the enum.
    };
};
