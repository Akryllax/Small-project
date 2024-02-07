#pragma once

#include "Rect.h"
#include "RenderCommand.h"
#include "allegro5/color.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace Akr::Renderer {
class DrawRectOperation : public RenderCommand {
public:
  DrawRectOperation(ALLEGRO_COLOR color, Akr::Math::Rect const& rect,
                    RenderCommandPriority const& _renderPriority = RenderCommand::RenderCommandPriority::DEFAULT)
      : RenderCommand(_renderPriority), color_(color), rect_(rect){};

  void execute() override { al_draw_filled_rectangle(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h, color_); }

private:
  DrawRectOperation() = delete;
  Akr::Math::Rect rect_;
  ALLEGRO_COLOR color_;
};
}  // namespace Akr::Renderer