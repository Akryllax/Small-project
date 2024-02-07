#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IEnableable.h"
#include "ITickable.h"
#include "RendererLayer.h"
#include "box2d/b2_math.h"
#include "allegro5/events.h"
#include <allegro5/allegro.h>
#include <array>
#include <climits>
#include <memory>
#include <vector>

namespace Akr::Input {
/**
 * @brief InputController class handles input events.
 */
class InputController : public IEnableable, ITickable {
public:
  struct InputEvent {
    enum class EVENT_TYPE { UNKNOWN = -1, NONE, KEYBOARD, MOUSE };

    const EVENT_TYPE eventType;
    const ALLEGRO_EVENT eventModifier;

    union {
      struct {
        int keyCode;
      } keyboardEvent;

      struct {
        int mouseX;
        int mouseY;
      } mouseEvent;
    };

  private:
    static inline EVENT_TYPE GetEventType(ALLEGRO_EVENT_TYPE eventCode) {
      // Check if the event code is in keyboardEvents
      if (std::find(std::begin(keyboardEvents), std::end(keyboardEvents), eventCode) != std::end(keyboardEvents)) {
        return EVENT_TYPE::KEYBOARD;
      }

      // Check if the event code is in mouseEvents
      if (std::find(std::begin(mouseEvents), std::end(mouseEvents), eventCode) != std::end(mouseEvents)) {
        return EVENT_TYPE::MOUSE;
      }

      return EVENT_TYPE::UNKNOWN;  // Default to UNKNOWN if not found in either keyboardEvents or mouseEvents
    }

    static constexpr ALLEGRO_EVENT_TYPE keyboardEvents[] = {ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_KEY_DOWN},
                                                            ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_KEY_UP},
                                                            ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_KEY_CHAR}};
    static constexpr ALLEGRO_EVENT_TYPE mouseEvents[] = {ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_MOUSE_AXES},
                                                         ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_MOUSE_BUTTON_DOWN},
                                                         ALLEGRO_EVENT_TYPE{ALLEGRO_EVENT_MOUSE_BUTTON_UP}};
  };

  /**
   * @brief Releases control of the input.
   */
  virtual inline void ReleaseControl() { isListening_ = true; }

  /**
   * @brief Takes control of the input.
   */
  virtual inline void TakeControl() { isListening_ = false; };

  /**
   * @brief Checks if the input is being listened to.
   * @return True if input is enabled and being listened to, false otherwise.
   */
  virtual inline bool IsListening() const { return IsEnabled() && isListening_; };

  /**
   * @brief Handles keyboard input.
   */
  virtual void HandleKeyboardInput(){};

  /**
   * @brief Handles mouse input.
   */
  virtual void HandleMouseInput(){};

  using ITickable::Tick;

  virtual ~InputController() = default;

protected:
  bool isListening_ = false;        /**< Flag indicating whether input is being listened to or not. */
  ALLEGRO_MOUSE_STATE mouseState_;  /**< State of the mouse. */
  ALLEGRO_KEYBOARD_STATE keyState_; /**< State of the keyboard. */
};

}  // namespace Akr::Input
