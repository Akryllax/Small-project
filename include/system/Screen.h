#pragma once

#include "box2d/b2_math.h"
#include "allegro5/display.h"
#include "spdlog/spdlog.h"

namespace Akr {

/**
 * @brief Screen class for managing screen properties.
 */
class Screen {
public:
  /**
   * @brief Gets the screen size.
   * @return Screen size as a b2Vec2.
   */
  static b2Vec2 getScreenSize() { return screenSize_; }

  static void ResizeDisplay(b2Vec2 newScreenSize)
  {
    if (!currentDisplay_) {
      spdlog::warn("Trying to resize an emtpy display, it was not registered");
    }

    // Implement here the resize function
    al_resize_display(currentDisplay_, newScreenSize.x, newScreenSize.y);
    desiredScreenSize_ = newScreenSize;
    updateScreenSize();
  };

  /**
   * @brief Registers the display.
   * @param display Pointer to the ALLEGRO_DISPLAY to register.
   */
  static void RegisterDisplay(ALLEGRO_DISPLAY* display) {
    if (currentDisplay_ != nullptr) {
      spdlog::warn("[{}] Overriding an existing display, old: {}, new: {}", __func__,
                   reinterpret_cast<uintptr_t>(currentDisplay_), reinterpret_cast<uintptr_t>(display));
    }

    currentDisplay_ = display;
    updateScreenSize();
  }

  /**
   * @brief Gets the registered display.
   * @return Pointer to the registered ALLEGRO_DISPLAY.
   */
  static ALLEGRO_DISPLAY* getDisplay() {
    if (!currentDisplay_) {
      spdlog::warn("Trying to get empty screen, it was not registered");
    }

    return currentDisplay_;
  };

private:
  inline static b2Vec2 screenSize_ = b2Vec2_zero;            /**< Screen size as a b2Vec2. */
  inline static b2Vec2 desiredScreenSize_ = b2Vec2_zero;
  inline static ALLEGRO_DISPLAY* currentDisplay_ = nullptr; /**< Pointer to the registered ALLEGRO_DISPLAY. */

  /**
   * @brief Updates the screen size based on the current display.
   */
  static void updateScreenSize() {
    auto display = getDisplay();

    if (display) {
      screenSize_.Set(al_get_display_width(display), al_get_display_height(display));
    }
  }
};

}  // namespace Akr
