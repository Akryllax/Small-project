#include "CompositeRenderCommand.h"
#include "DrawRectOperation.h"
#include "DrawTextCommand.h"
#include "IControllable.h"
#include "IRenderable.h"
#include "Rect.h"
#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include "color.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_ttf.h>
#include <memory>
#include <string>

namespace Akr::UI {
class Button : public Akr::IControllable, public Akr::IRenderable {
public:
  Button(int x, int y, int width, int height, char const* label)
      : buttonRect_(
            {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}),
        label_(label) {
    pressed_ = false;
    textRect_ = Math::Rect::GetCenteredRect(buttonRect_, Renderer::DrawTextCommand::CalculateTextRect(al_create_builtin_font(), label_));
  }

  bool isMouseOver(int mouseX, int mouseY) {
    return mouseX >= buttonRect_.x && mouseX <= buttonRect_.x + buttonRect_.w && mouseY >= buttonRect_.y && mouseY <= buttonRect_.y + buttonRect_.h;
  }

  [[deprecated("Please, migrate to RenderOperation, prettyplz")]] void draw() {
    // al_draw_filled_rectangle(x, y, x + width, y + height, pressed_ ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0));
    // al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255), x + width / 2, y + height / 2,
    //              ALLEGRO_ALIGN_CENTRE, label_.c_str());
  }

  void handleClick() {
    pressed_ = true;
    // Implement your action here when the button is clicked.
  }
  std::string label_;

  Math::Rect buttonRect_;
  Math::Rect textRect_;

  bool pressed_;
  void release() { pressed_ = false; }

  virtual void TakeControl() override{};
  virtual void ReleaseControl() override{};

  virtual void OnEvent() override{};

  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override {
    auto composideOperation = std::make_shared<Renderer::CompositeRenderComand>();
    composideOperation->QueueCommand(std::make_shared<Renderer::DrawRectOperation>(
        al_map_rgb(120, 0, 0), buttonRect_));

    composideOperation->QueueCommand(
        std::make_shared<Renderer::DrawTextCommand>(label_, b2Vec2{static_cast<float>(textRect_.x), static_cast<float>(textRect_.y)},
                                                    al_create_builtin_font(), al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER));
    return composideOperation;
  };

  // class DrawButtonOperation : public Akr::Renderer::RenderCommand {
  //   void execute() override{

  //   };
  // };
};
}  // namespace Akr::UI