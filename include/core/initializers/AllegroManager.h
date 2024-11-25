#pragma once

#include <cstdint>
#include <memory>
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "TestShip.h"
#include "Button.h"

namespace Akr {

/**
 * @brief The AllegroManager struct manages the initialization, running, and cleanup
 * of the Allegro library and resources.
 */
struct AllegroManager {
public:
    /**
     * @brief Initializes the Allegro library and resources.
     * @return Returns 0 on success, or an error code otherwise.
     */
    static int Initialize();

    /**
     * @brief Runs the main loop of the application.
     * @return Returns 0 on success, or an error code otherwise.
     */
    static int Run();

    /**
     * @brief Cleans up and deallocates resources used by the Allegro library.
     * @return Returns 0 on success, or an error code otherwise.
     */
    static int Cleanup();

    /**
     * @brief The default frames per second (FPS) for the application.
     */
    static constexpr uint16_t DEFAULT_FPS = 30;

    /**
     * @brief The main event queue used by Allegro.
     */
    inline static ALLEGRO_EVENT_QUEUE* mainQueue;

    /**
     * @brief The system display managed by Allegro.
     */
    inline static ALLEGRO_DISPLAY* systemDisplay;

    /**
     * @brief The internal buffer used for rendering.
     */
    inline static ALLEGRO_BITMAP* internalBuffer;

    /**
     * @brief The main font used for text rendering.
     */
    inline static ALLEGRO_FONT* mainFont;

    inline static std::chrono::high_resolution_clock::time_point applicationEpoch;

private:
    /**
     * @brief Installs necessary Allegro systems.
     */
    static void InstallAllegroSystems();

    /**
     * @brief Creates the main display.
     */
    static void CreateDisplay();

    /**
     * @brief Loads basic resources required for the application.
     */
    static void LoadBasicResources();

    /**
     * @brief Creates event queues and timers.
     */
    static void CreateEventAndTimers();

    /**
     * @brief Loads a development scene for testing purposes.
     */
    static void LoadDevScene();

    static void LoadSimpleDevScene();

    static void HandleEngineLoopTick();

    static void EngineTickFrame(std::chrono::milliseconds const&);

    static void EngineStableTick(std::chrono::milliseconds const&);

    static void MainLoop();


    inline static bool quitApplication_ = false;
};

}  // namespace Akr::Init
