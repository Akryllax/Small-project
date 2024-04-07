#pragma once

#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "DrawRectAlpha.h"
#include "DrawTextCommand.h"
#include "IControllable.h"
#include "IRenderable.h"
#include "Rect.h"
#include "RenderCommand.h"
#include "spdlog/spdlog.h"
#include <box2d/b2_math.h>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

namespace Akr::UI {
class UIRectangle : public Akr::IRenderable, public Akr::IControllable {
public:
  UIRectangle(int x, int y, int width, int height, ALLEGRO_COLOR color, float transparency) : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color), m_transparency(transparency)
  {
    Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderablePtr(this);
  }
  void TakeControl() override{};
  void ReleaseControl() override{};

  void OnEvent() override{};

  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override {
    ALLEGRO_COLOR rectColor;
    spdlog::trace("[UIRectangle] Generating render command");
    return compositeOperation_;
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
      int mouseX = mouseState.x;
      int mouseY = mouseState.y;
      if (!pressed_) {
        spdlog::trace("[UIRectangle] Mouse pressed, setting initial drag position to: ({}, {})", mouseX, mouseY);
        intialDragPosition_ = b2Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
        pressed_ = true;
      }


      spdlog::trace("[UIRectangle] Drawing rectangle at: ({}, {}), w: {}, h: {}", intialDragPosition_.x, intialDragPosition_.y, intialDragPosition_.x + mouseX, intialDragPosition_.y + mouseY, 0);
      ALLEGRO_COLOR rectColor = al_map_rgb(0, 0, 255);

      spdlog::trace("[UIRectangle] Creating composite render command");
      auto compositeOperation = std::make_shared<Renderer::CompositeRenderComand>();
      auto rectCommand = std::make_shared<Renderer::DrawRectAlphaOperation>(
          rectColor, Math::Rect{intialDragPosition_.x, intialDragPosition_.y, intialDragPosition_.x + mouseX, intialDragPosition_.y + mouseY, 0}, 0);
      compositeOperation->QueueCommand(rectCommand);
    } else if(!(mouseState.buttons & 1) && pressed_){
      spdlog::trace("[UIRectangle] Mouse released, setting pressed to false");
      pressed_ = false;
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
  std::shared_ptr<Renderer::CompositeRenderComand> compositeOperation_;
};

}  // namespace Akr::UI
