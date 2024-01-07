#include "LibDef.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

#ifndef FRAMERATE
#define FRAMERATE

/**
 * @class FrameRate
 * @brief Manages and calculates the frame rate for a graphics application.
 *
 * This class is designed to track and calculate the frames per second (fps) in a graphics
 * application. It is useful for performance monitoring and ensuring that rendering is occurring
 * at the desired rate.
 */
class LIB_API FrameRate {
public:
    /**
     * @brief Constructor for the FrameRate class.
     *
     * Initializes a new instance of the FrameRate class with initial values.
     */
    FrameRate();

    /**
     * @brief Destructor for the FrameRate class.
     *
     * Performs cleanup tasks for the FrameRate instance, if necessary.
     */
    ~FrameRate();

public:
    /**
     * @brief Retrieves the current frames per second (FPS).
     *
     * This method returns the calculated FPS value, which indicates the performance
     * of the graphics rendering.
     *
     * @return An integer representing the current FPS.
     */
    int getFps();

    /**
     * @brief Calculates the frame rate based on time elapsed.
     *
     * This method updates the FPS value by calculating it based on the time elapsed
     * since the last frame. It should be called once per frame.
     */
    void calculateFrameRate();

private:
    int fps = 0; ///< The calculated frames per second.
    int fpsTmp = 0; ///< A temporary storage for FPS calculation.
    time_t lastTime = 0.0f; ///< The time at which the last FPS calculation was made.
    time_t currentTime = 0.0f; ///< The current time for the ongoing FPS calculation.
};

#endif // FRAMERATE
