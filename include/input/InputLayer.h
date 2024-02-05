#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IEnableable.h"
#include "ITickable.h"
#include "InputController.h"
#include "RendererLayer.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro.h>
#include <climits>
#include <memory>
#include <vector>

namespace Akr {

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
  void AddController(std::shared_ptr<Akr::Input::InputController> controller) { this->controllerList.push_back(controller); }

  /**
   * @brief Gets the mouse screen position.
   * @return Mouse screen position.
   */
  b2Vec2 GetMouseScreenPosition() const { return b2Vec2(); }

private:
  std::vector<std::shared_ptr<Akr::Input::InputController>> controllerList; /**< List of input controllers. */
};

} // namespace Akr
