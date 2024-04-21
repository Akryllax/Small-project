#pragma once

#include "RenderCommand.h"
#include "allegro5/allegro.h"
#include "math/Rect.h"
#include <allegro5/allegro_primitives.h>

namespace Akr::Renderer {
class DrawBoundingBoxCommand : public RenderCommand {
public:
  DrawBoundingBoxCommand(Math::Rect const& _rect, ALLEGRO_COLOR _color,
                        RenderCommandPriority const& _renderPriority = RenderCommand::RenderCommandPriority::DEFAULT)
      : RenderCommand(_renderPriority), rect_(_rect), color_(_color){};

  void execute() override {
    al_draw_rectangle(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h, color_, 1);
  };
  DrawBoundingBoxCommand() = delete;
  DrawBoundingBoxCommand(DrawBoundingBoxCommand const&) = delete;

  Math::Rect rect_;
  ALLEGRO_COLOR color_;
};
}  // namespace Akr::Renderer