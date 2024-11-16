#include "Button.h"
#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "Core.h"
#include "DrawRectOperation.h"
#include "DrawTextCommand.h"
#include "RenderCommand.h"
#include "RendererLayer.h"

namespace Akr::UI {
Button::Button(int x, int y, int width, int height, char const* label, std::uint8_t id)
    : UIElement(UIElement::Type::BUTTON, id),
      label_(label),
      buttonRect_({static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}) {
  pressed_ = false;

  textRect_ = Math::Rect::GetCenteredRect(buttonRect_, Renderer::DrawTextCommand::CalculateTextRect(Akr::AllegroManager::mainFont, label_));

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderablePtr(this);
}

void Button::OnRawInput(std::chrono::milliseconds const& delta) {
  IControllable::OnRawInput(delta);

  // Get the current mouse state
  ALLEGRO_MOUSE_STATE mouseState;
  al_get_mouse_state(&mouseState);

  // Get the current mouse position
  int mouseX = mouseState.x;
  int mouseY = mouseState.y;

  // Check for mouse over
  bool isMouseOverButton = isMouseOver(mouseX, mouseY);

  // Check for mouse click
  if (mouseState.buttons & 1 && !pressed_) {
    // Left mouse button is pressed while over the button
    // Handle button click event
    buttonDownPos_ = {static_cast<float>(mouseX), static_cast<float>(mouseY)};

    if (isMouseOverButton) {
      pressed_ = true;
      handleClick();
    }
  } else if (!(mouseState.buttons & 1)) {
    // Mouse button is released
    pressed_ = false;
  }

  // Check for mouse leave
  if (!isMouseOverButton && mouseWasOverButton_) {
    // Mouse has left the button's area
    // Handle mouse leave event
  }

  // Update the mouse state for the next frame
  mouseWasOverButton_ = isMouseOverButton;
}

bool Button::isMouseOver(int mouseX, int mouseY) const {
  return mouseX >= buttonRect_.x && mouseX <= buttonRect_.x + buttonRect_.w && mouseY >= buttonRect_.y &&
         mouseY <= buttonRect_.y + buttonRect_.h;
}

void Button::SetOnClick(std::function<void()> onClick) { onClick_ = onClick; }

std::shared_ptr<Renderer::RenderCommand> Button::GenerateRenderCommand() {
  ALLEGRO_COLOR rectColor;

  if (!pressed_ && !mouseWasOverButton_) {
    rectColor = al_map_rgb(200, 100, 100);
  } else if (pressed_) {
    rectColor = al_map_rgb(200, 120, 120);
  } else {
    rectColor = al_map_rgb(200, 80, 80);
  }

  auto composideOperation = std::make_shared<Renderer::CompositeRenderComand>();
  composideOperation->QueueCommand(std::make_shared<Renderer::DrawRectOperation>(rectColor, buttonRect_));

  composideOperation->QueueCommand(
      std::make_shared<Renderer::DrawTextCommand>(label_, b2Vec2{static_cast<float>(textRect_.x), static_cast<float>(textRect_.y)},
                                                  Akr::AllegroManager::mainFont, al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER));
  return composideOperation;
}

void Button::release() { pressed_ = false; }

void Button::handleClick() {
  pressed_ = true;
  OnClick();
}

void Button::OnClick() {
  if (onClick_) {
    onClick_();
  }
}
}  // namespace Akr::UI
