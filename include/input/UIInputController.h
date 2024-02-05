#pragma once

#include "InputController.h"

namespace Akr::Input {

/**
 * @brief UIInputControler class for handling UI input.
 */
class UIInputControler : public Akr::Input::InputController {
public:
  using InputController::InputController;

  void Tick(std::chrono::milliseconds const& delta) override {
    InputController::Tick(delta);

    al_get_mouse_state(&mouseState_);

    auto coreRenderer = Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer();

    coreRenderer.DrawText(
        fmt::format("mousePos: ({}, {})", mouseState_.x, mouseState_.y), b2Vec2(0, 0));
    coreRenderer.DrawCross(b2Vec2(500, 400));
  };
};
} // namespace Akr::Input
