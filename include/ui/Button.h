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

namespace Akr {
  namespace UI {
    class Button : public IControllable, public IRenderable {
    public:
      Button(int x, int y, int width, int height, const char* label);

      void OnRawInput(std::chrono::milliseconds const& delta) override;

      bool isMouseOver(int mouseX, int mouseY);

      void SetOnClick(std::function<void()> onClick);

      virtual void TakeControl() override{};
      virtual void ReleaseControl() override{};

      virtual void OnEvent() override{};

      virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override;

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
  } // namespace UI
} // namespace Akr
