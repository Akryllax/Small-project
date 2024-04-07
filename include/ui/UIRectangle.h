#pragma once

#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "DrawCrossOperation.h"
#include "DrawRectAlpha.h"
#include "DrawTextCommand.h"
#include "IControllable.h"
#include "IRenderable.h"
#include "Rect.h"
#include "RenderCommand.h"
#include "spdlog/spdlog.h"
#include <box2d/b2_math.h>
#include <chrono>
#include <memory>
#include <string>

namespace Akr::UI {
class UIRectangle : public Akr::IRenderable, public Akr::IControllable {
public:
  UIRectangle(int x, int y, int width, int height, ALLEGRO_COLOR color, float transparency)
      : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color), m_transparency(transparency), pressed_(false) {
        Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterUIRenderablePtr(this);
  }
  void TakeControl() override{};
  void ReleaseControl() override{};

  void OnEvent() override{};

  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override {
    ALLEGRO_COLOR rectColor = m_color;
    spdlog::trace("[UIRectangle] Generating render command");
    auto compositeOperation = std::make_shared<Renderer::CompositeRenderComand>();

    auto initialPositionCross = std::make_shared<Renderer::DrawCrossCommand>(intialDragPosition_, al_map_rgb(0, 255, 0));
    compositeOperation->QueueCommand(initialPositionCross);

    if (pressed_) {
      auto currentPositionCross = std::make_shared<Renderer::DrawCrossCommand>(dbgCurrentDragPosition_, al_map_rgb(0, 255, 0));
      compositeOperation->QueueCommand(currentPositionCross);
    }
    auto finalinitialPositionCross = std::make_shared<Renderer::DrawCrossCommand>(dbgFinalDragPosition_, (pressed_) ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 255, 255));
    compositeOperation->QueueCommand(finalinitialPositionCross);

    auto mouseDelta = dbgCurrentDragPosition_ - dbgInitialDragPosition_;

    if (pressed_ && mouseDelta.x != 0 && mouseDelta.y != 0) {
      auto rectCommand = std::make_shared<Renderer::DrawRectAlphaOperation>(
          rectColor,
          Math::Rect{static_cast<float>(dbgInitialDragPosition_.x),
          static_cast<float>(dbgInitialDragPosition_.y),
                     static_cast<float>(mouseDelta.x),
                     static_cast<float>(mouseDelta.y)},
          m_transparency);

      compositeOperation->QueueCommand(rectCommand);
    }

    //!TODO: Fix this, as we need to return a valid compositeOperation, currently we are hijacking the core renderer logic.
    // Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetUiRenderer().addCommand(compositeOperation);

    return compositeOperation;
  }

  void OnRawInput(std::chrono::milliseconds const& delta) override {
    spdlog::trace("[UIRectangle] OnRawInput");
    IControllable::OnRawInput(delta);

    // Get the current mouse state
    ALLEGRO_MOUSE_STATE mouseState;
    al_get_mouse_state(&mouseState);
    spdlog::trace("[UIRectangle] Getting mouse state: L mouse: {}, R mosue: {}", mouseState.buttons & 1, mouseState.buttons & 2);

    if (mouseState.buttons & 1 || pressed_) {  // If left mouse button is pressed
      // Get the current mouse position
      m_x = mouseState.x;
      m_y = mouseState.y;
      if (!pressed_) {
        spdlog::trace("[UIRectangle] Mouse pressed, setting initial drag position to: ({}, {})", m_x, m_y);
        intialDragPosition_ = b2Vec2(static_cast<float>(m_x), static_cast<float>(m_y));
        dbgInitialDragPosition_ = intialDragPosition_;
        dbgCurrentDragPosition_ = intialDragPosition_;
        pressed_ = true;
      } else {
        spdlog::trace("[UIRectangle] Mouse dragged, setting current drag position to: ({}, {})", m_x, m_y);
        dbgCurrentDragPosition_ = b2Vec2(static_cast<float>(m_x), static_cast<float>(m_y));
      }

      spdlog::trace("[UIRectangle] Drawing rectangle at: ({}, {}), w: {}, h: {}", intialDragPosition_.x, intialDragPosition_.y,
                    intialDragPosition_.x + m_x, intialDragPosition_.y + m_y, 0);
      ALLEGRO_COLOR rectColor = al_map_rgb(0, 0, 255);
    }

    if (!(mouseState.buttons & 1) && pressed_) {  // If left mouse button is released
      spdlog::trace("[UIRectangle] Mouse released, setting pressed to false");
      pressed_ = false;
      dbgFinalDragPosition_ = dbgCurrentDragPosition_;
      intialDragPosition_ = b2Vec2(0, 0);
    }
  }

private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  ALLEGRO_COLOR m_color;
  float m_transparency;
  bool pressed_;
  bool mouseWasOverButton_;
  Math::Rect buttonRect_;
  std::string label_;
  Math::Rect textRect_;
  b2Vec2 intialDragPosition_;

  b2Vec2 dbgInitialDragPosition_;
  b2Vec2 dbgCurrentDragPosition_;
  b2Vec2 dbgFinalDragPosition_;
};

}  // namespace Akr::UI
