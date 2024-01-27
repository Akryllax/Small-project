#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IEnableable.h"
#include "ITickable.h"
#include "RendererLayer.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro.h>
#include <climits>
#include <memory>
#include <vector>

namespace Akr {

/**
 * @brief InputController class handles input events.
 */
class InputController : public IEnableable, ITickable {
public:
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

  // void HandleKeyboardInput() {
  //   ALLEGRO_KEYBOARD_STATE keyState_;
  //   al_get_keyboard_state(&keyState_);

  //   // Example: Check if the key 'A' is pressed
  //   if (al_key_down(&keyState, ALLEGRO_KEY_A)) {
  //     // Handle 'A' key press
  //   }

  //   // Add more key checks as needed
  // }

  // void HandleMouseInput() {
  //   al_get_mouse_state(&mouseState);

  //   // Example: Check if the left mouse button is pressed
  //   if (al_mouse_button_down(&mouseState, 1)) {
  //     // Handle left mouse button press
  //   }

  //   // Add more mouse button checks as needed
  // }

  virtual ~InputController() = default;

protected:
  bool isListening_ = false;        /**< Flag indicating whether input is being listened to or not. */
  ALLEGRO_MOUSE_STATE mouseState_;  /**< State of the mouse. */
  ALLEGRO_KEYBOARD_STATE keyState_; /**< State of the keyboard. */
};

/**
 * @brief UIInputControler class for handling UI input.
 */
class UIInputControler : public InputController {
public:
  using InputController::InputController;

  void Tick(std::chrono::milliseconds const delta) override {
    InputController::Tick(delta);

    al_get_mouse_state(&mouseState_);

    Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer().DrawText(
        fmt::format("mousePos: ({}, {})", mouseState_.x, mouseState_.y), b2Vec2(0, 0));
  };
};

/**
 * @brief InputLayer class manages input controllers.
 */
class InputLayer : public DataLayer {
public:
  constexpr static size_t EXEC_PRIORITY = 101; /**< Execution priority of the input layer. */

  /**
   * @brief Returns the execution priority of the input layer.
   * @return Execution priority.
   */
  size_t GetExecPriority() const override { return EXEC_PRIORITY; }

  using DataLayer::Initialize;

  /**
   * @brief Executes tick for all input controllers.
   * @param delta Time delta.
   */
  void Tick(std::chrono::milliseconds const delta) override {
    spdlog::trace("InputLayer::Tick()");
    for (auto controller : controllerList) {
      controller->Tick(delta);
    }
  }

  /**
   * @brief Adds an input controller.
   * @param controller Input controller to add.
   */
  void AddController(std::shared_ptr<InputController> controller) { this->controllerList.push_back(controller); }

  /**
   * @brief Gets the mouse screen position.
   * @return Mouse screen position.
   */
  b2Vec2 GetMouseScreenPosition() const { return b2Vec2(); }

private:
  std::vector<std::shared_ptr<InputController>> controllerList; /**< List of input controllers. */
};

} // namespace Akr
