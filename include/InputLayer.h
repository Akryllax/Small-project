#pragma once

#include "DataLayer.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro.h>

namespace Akr {

class InputLayer : public DataLayer {
 public:
  void Tick(std::chrono::milliseconds const delta) override {
    HandleKeyboardInput();
    HandleMouseInput();
  }

 b2Vec2 GetMouseScreenPosition() const { return b2Vec2(); }

 private:
  void HandleKeyboardInput() {
    ALLEGRO_KEYBOARD_STATE keyState_;
    al_get_keyboard_state(&keyState_);

    // Example: Check if the key 'A' is pressed
    if (al_key_down(&keyState, ALLEGRO_KEY_A)) {
      // Handle 'A' key press
    }

    // Add more key checks as needed
  }

  void HandleMouseInput() {
    al_get_mouse_state(&mouseState);

    // Example: Check if the left mouse button is pressed
    if (al_mouse_button_down(&mouseState, 1)) {
      // Handle left mouse button press
    }

    // Add more mouse button checks as needed
  }

  ALLEGRO_MOUSE_STATE mouseState;
  ALLEGRO_KEYBOARD_STATE keyState;
};

}  // namespace Akr
