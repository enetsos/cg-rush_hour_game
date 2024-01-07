#pragma once

/**
 * @class OvLight
 * @brief Represents a light object with different subtypes.
 *
 * This class is a simplified version of OvLight, focusing solely on the subtypes of lights
 * that can be represented. It includes an enumeration for different kinds of light such as
 * Omni, Directional, and Spot lights.
 */
class OvLight
{
public:
    /**
     * @enum Subtype
     * @brief Enumerates the different subtypes of lights.
     *
     * This enumeration is used to specify the kind of light, including foundational types
     * like Omni, Directional, and Spot lights. It also includes a 'LAST' value as a terminator.
     */
    enum class Subtype : int ///< Kind of light
    {
        OMNI = 0,       ///< Represents an Omni light, emitting light uniformly in all directions.
        DIRECTIONAL,    ///< Represents a Directional light, simulating a distant light source like the sun.
        SPOT,           ///< Represents a Spot light, emitting light in a specific direction with a conical spread.

        LAST,           ///< Terminator for the enumeration, used to mark the end of the enum.
    };
};
