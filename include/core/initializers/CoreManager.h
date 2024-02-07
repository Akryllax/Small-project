#pragma once

namespace Akr {

/**
 * @brief The CoreManager class manages initialization and cleanup tasks related to the core functionality of the application.
 */
class CoreManager {
public:
    /**
     * @brief Initializes the core functionality of the application.
     * @return Returns 0 on success, or an error code otherwise.
     */
    static int Initialize();

    /**
     * @brief Cleans up and deallocates resources used by the core functionality of the application.
     * @return Returns 0 on success, or an error code otherwise.
     */
    static int Cleanup();
};

}  // namespace Akr::Init
