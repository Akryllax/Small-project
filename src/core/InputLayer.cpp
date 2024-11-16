#include "InputLayer.h"
#include <spdlog/spdlog.h> // Include spdlog for logging

namespace Akr {

void InputLayer::Tick(std::chrono::milliseconds const& delta) {
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

void InputLayer::AddController(std::shared_ptr<Akr::Input::InputController> controller) {
  this->controllerList_.push_back(controller);
}

void InputLayer::RegisterRawInputListener(std::shared_ptr<IControllable> controllable) {
  this->rawControllables_.push_back(controllable);
}

void InputLayer::AddControllerPtr(Akr::Input::InputController* controller) {
  this->controllerPtrList_.push_back(controller);
}

void InputLayer::RegisterRawInputListenerPtr(Akr::IControllable* controllable) {
  this->rawControllablesPtrs_.push_back(controllable);
}

void InputLayer::ClearAllInputs() {
  invalidateControllerList_ = true;
  invalidateControllerPtrList_ = true;
  invalidateRawControllables_ = true;
  invalidateRawControllablesPtrs_ = true;
}

void InputLayer::ClearControllers() {
  invalidateControllerList_ = true;
}

void InputLayer::ClearControllerPtrs() {
  invalidateControllerPtrList_ = true;
}

void InputLayer::ClearRawInputListeners() {
  invalidateRawControllables_ = true;
  invalidateRawControllablesPtrs_ = true;
}

void InputLayer::SelectInputLayer(InputLayer* _inputLayer) {
  if (_inputLayer != nullptr) {
    selectedInputLayer_ = _inputLayer;
    spdlog::info("[InputLayer] Input layer selected successfully."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to select input layer: _inputLayer is nullptr."); // Log failure
  }
}

void InputLayer::AddControllerStatic(std::shared_ptr<Akr::Input::InputController> controller) {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->AddController(controller);
    spdlog::info("[InputLayer] Controller added."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to add controller: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::RegisterRawInputListenerStatic(std::shared_ptr<IControllable> controllable) {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->RegisterRawInputListener(controllable);
    spdlog::info("[InputLayer] Raw input listener registered."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to register raw input listener: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::AddControllerPtrStatic(Akr::Input::InputController* controller) {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->AddControllerPtr(controller);
    spdlog::info("[InputLayer] Controller pointer added."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to add controller pointer: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::RegisterRawInputListenerPtrStatic(Akr::IControllable* controllable) {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->RegisterRawInputListenerPtr(controllable);
    spdlog::info("[InputLayer] Raw input listener pointer registered."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to register raw input listener pointer: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::ClearAllInputsStatic() {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->ClearAllInputs();
    spdlog::info("[InputLayer] All inputs cleared."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to clear all inputs: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::ClearControllersStatic() {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->ClearControllers();
    spdlog::info("[InputLayer] Controllers cleared."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to clear controllers: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::ClearControllerPtrsStatic() {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->ClearControllerPtrs();
    spdlog::info("[InputLayer] Controller pointers cleared."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to clear controller pointers: selectedInputLayer_ is nullptr."); // Log failure
  }
}

void InputLayer::ClearRawInputListenersStatic() {
  if (selectedInputLayer_ != nullptr) {
    selectedInputLayer_->ClearRawInputListeners();
    spdlog::info("[InputLayer] Raw input listeners cleared."); // Log success
  } else {
    spdlog::error("[InputLayer] Failed to clear raw input listeners: selectedInputLayer_ is nullptr."); // Log failure
  }
}

}  // namespace Akr