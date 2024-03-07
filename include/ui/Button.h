#pragma once

#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "DrawRectOperation.h"
#include "DrawTextCommand.h"
#include "IControllable.h"
#include "IRenderable.h"
#include "Rect.h"
#include <chrono>
#include <functional>
#include <string>

namespace Akr::UI {
class Button : public IControllable, public IRenderable {
public:
  Button(int x, int y, int width, int height, char const* label);

  void OnRawInput(std::chrono::milliseconds const& delta) override;

  bool isMouseOver(int mouseX, int mouseY) const;

  void SetOnClick(std::function<void()> onClick);

  void TakeControl() override{/* Override to implement custom functionality */};
  void ReleaseControl() override{/* Override to implement custom functionality */};

  void OnEvent() override{/* Override to implement custom functionality */};

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
}  // namespace Akr::UI
