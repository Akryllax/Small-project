#pragma once

#include <climits>
#include <memory>
#include <vector>
#include <allegro5/allegro.h>
#include "box2d/b2_math.h"

#include "Core.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IControllable.h"
#include "IEnableable.h"
#include "ITickable.h"
#include "InputController.h"
#include "RendererLayer.h"
#include "UIAction.h"
#include "IndexedVector.h"

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

  InputLayer() {
    //!TECH_DEBT: This is a temporary solution to ensure that the selectedInputLayer_ is not null and static methods have something.
    if(!selectedInputLayer_) selectedInputLayer_ = this;
  }

  /**
   * @brief Executes tick for all input controllers.
   * @param delta Time delta.
   */
  void Tick(std::chrono::milliseconds const& delta) override;

  /**
   * @brief Adds an input controller.
   * @param controller Input controller to add.
   */
  void AddController(std::shared_ptr<Akr::Input::InputController> controller);

  void RegisterRawInputListener(std::shared_ptr<IControllable> controllable);

  /**
   * @brief Adds an input controller.
   * @param controller Input controller to add.
   */
  void AddControllerPtr(Akr::Input::InputController* controller);

  void RegisterRawInputListenerPtr(Akr::IControllable* controllable);

  /**
   * @brief Clears all input controllers and raw input listeners.
   */
  void ClearAllInputs();

  /**
   * @brief Clears all input controllers.
   */
  void ClearControllers();

  /**
   * @brief Clears all input controller pointers.
   */
  void ClearControllerPtrs();

  /**
   * @brief Clears all raw input listeners.
   */
  void ClearRawInputListeners();

#pragma region Static Interface
  static void SelectInputLayer(InputLayer* _inputLayer);

  static void AddControllerStatic(std::shared_ptr<Akr::Input::InputController> controller);

  static void RegisterRawInputListenerStatic(std::shared_ptr<IControllable> controllable);

  static void AddControllerPtrStatic(Akr::Input::InputController* controller);

  static void RegisterRawInputListenerPtrStatic(Akr::IControllable* controllable);

  static void ClearAllInputsStatic();

  static void ClearControllersStatic();

  static void ClearControllerPtrsStatic();

  static void ClearRawInputListenersStatic();
#pragma endregion

private:
  static inline InputLayer* selectedInputLayer_ = nullptr;

  std::vector<std::shared_ptr<Akr::Input::InputController>> controllerList_; /**< List of input controllers. */
  std::vector<std::shared_ptr<Akr::IControllable>> rawControllables_;

  std::vector<Akr::Input::InputController*> controllerPtrList_; /**< List of input controllers. */
  std::vector<Akr::IControllable*> rawControllablesPtrs_;

  Akr::Util::IndexedVector<Akr::Input::UIAction> uiActions_; /**< Indexed vector of UI actions. */

  bool invalidateControllerList_ = false;       /**< Flag indicating if the controllerList_ vector is invalidated. */
  bool invalidateRawControllables_ = false;     /**< Flag indicating if the rawControllables_ vector is invalidated. */
  bool invalidateControllerPtrList_ = false;    /**< Flag indicating if the controllerPtrList_ vector is invalidated. */
  bool invalidateRawControllablesPtrs_ = false; /**< Flag indicating if the rawControllablesPtrs_ vector is invalidated. */
};

}  // namespace Akr