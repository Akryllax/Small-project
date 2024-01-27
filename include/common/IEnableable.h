#pragma once

namespace Akr {
/**
 * @brief Interface for objects that can be enabled or disabled.
 */
class IEnableable {
public:
    /**
     * @brief Enables the object.
     */
    inline void Enable() { isEnabled_ = true; }

    /**
     * @brief Disables the object.
     */
    inline void Disable() { isEnabled_ = false; }

    /**
     * @brief Checks if the object is enabled.
     * @return True if the object is enabled, false otherwise.
     */
    inline bool IsEnabled() const { return isEnabled_; }

private:
    bool isEnabled_ = false; /**< Flag indicating whether the object is enabled or disabled. */
};
} // namespace Akr
