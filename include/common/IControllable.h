#pragma once

#include "InputController.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace Akr {

struct IControllable {
public:
  virtual ~IControllable() = default;

  inline virtual void RegisterController(std::shared_ptr<Akr::Input::InputController> controller) {
    controller_ = controller;
  };
  virtual void TakeControl() = 0;
  virtual void ReleaseControl() = 0;

  virtual void OnEvent() = 0;

  // Process raw input here, will be called in any InputEvent
  virtual void OnRawInput(std::chrono::milliseconds const& delta){
    spdlog::trace("[IControllable] OnRawInput() called");
  };

private:
  std::shared_ptr<Akr::Input::InputController> controller_;
};
};  // namespace Akr