#pragma once

#include "InputController.h"
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

private:
  std::shared_ptr<Akr::Input::InputController> controller_;
};
};  // namespace Akr