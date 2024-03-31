#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IControllable.h"
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
  void Tick(std::chrono::milliseconds const& delta) override {
    spdlog::trace("[InputLayer] Tick()");
    for (auto controller : controllerList_) {
      controller->Tick(delta);
    }

    for (auto rawControllable : rawControllables_) {
      rawControllable->OnRawInput(delta);
    }

    for (auto controllerPtr : controllerPtrList_) {
      controllerPtr->Tick(delta);
    }

    for (auto rawControllablePtr : rawControllablesPtrs_) {
      rawControllablePtr->OnRawInput(delta);
    }

    if (invalidateControllerList_) {
      controllerList_.clear();
      invalidateControllerList_ = false;
    }

    if (invalidateRawControllables_) {
      rawControllables_.clear();
      invalidateRawControllables_ = false;
    }

    if (invalidateControllerPtrList_) {
      controllerPtrList_.clear();
      invalidateControllerPtrList_ = false;
    }

    if (invalidateRawControllablesPtrs_) {
      rawControllablesPtrs_.clear();
      invalidateRawControllablesPtrs_ = false;
    }
  }

  /**
   * @brief Adds an input controller.
   * @param controller Input controller to add.
   */
  void AddController(std::shared_ptr<Akr::Input::InputController> controller) { this->controllerList_.push_back(controller); }

  void RegisterRawInputListener(std::shared_ptr<IControllable> controllable) { this->rawControllables_.push_back(controllable); };

  /**
   * @brief Adds an input controller.
   * @param controller Input controller to add.
   */
  void AddControllerPtr(Akr::Input::InputController* controller) { this->controllerPtrList_.push_back(controller); }

  void RegisterRawInputListenerPtr(Akr::IControllable* controllable) { this->rawControllablesPtrs_.push_back(controllable); };

  /**
   * @brief Clears all input controllers and raw input listeners.
   */
  void ClearAllInputs() {
    invalidateControllerList_ = true;
    invalidateControllerPtrList_ = true;
    invalidateRawControllables_ = true;
    invalidateRawControllablesPtrs_ = true;
  }

  /**
   * @brief Clears all input controllers.
   */
  void ClearControllers() { invalidateControllerList_ = true; }

  /**
   * @brief Clears all input controller pointers.
   */
  void ClearControllerPtrs() { invalidateControllerPtrList_ = true; }

  /**
   * @brief Clears all raw input listeners.
   */
  void ClearRawInputListeners() {
    invalidateRawControllables_ = true;
    invalidateRawControllablesPtrs_ = true;
  }

private:
  std::vector<std::shared_ptr<Akr::Input::InputController>> controllerList_; /**< List of input controllers. */
  std::vector<std::shared_ptr<Akr::IControllable>> rawControllables_;

  std::vector<Akr::Input::InputController*> controllerPtrList_; /**< List of input controllers. */
  std::vector<Akr::IControllable*> rawControllablesPtrs_;

  bool invalidateControllerList_ = false;       /**< Flag indicating if the controllerList_ vector is invalidated. */
  bool invalidateRawControllables_ = false;     /**< Flag indicating if the rawControllables_ vector is invalidated. */
  bool invalidateControllerPtrList_ = false;    /**< Flag indicating if the controllerPtrList_ vector is invalidated. */
  bool invalidateRawControllablesPtrs_ = false; /**< Flag indicating if the rawControllablesPtrs_ vector is invalidated. */
};

}  // namespace Akr
