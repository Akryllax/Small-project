#pragma once

#include "IControllable.h"
#include "UIElement.h"
#include "Rect.h"
#include <chrono>
#include <functional>
#include <string>

namespace Akr::UI {
class Button : public UIElement, public IControllable {
public:
  Button(int x, int y, int width, int height, const char* label, std::uint8_t id = 0);

  void OnRawInput(std::chrono::milliseconds const& delta) override;

  bool isMouseOver(int mouseX, int mouseY) const;

  void SetOnClick(std::function<void()> onClick);

  void TakeControl() override {};
  void ReleaseControl() override {};

  void OnEvent() override {};

  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override;

  void release();

private:
  void handleClick();
  void OnClick();

  std::string label_;
  Math::Rect buttonRect_;
  Math::Rect textRect_;

  bool pressed_;
  bool mouseWasOverButton_;

  std::function<void()> onClick_;
};
}