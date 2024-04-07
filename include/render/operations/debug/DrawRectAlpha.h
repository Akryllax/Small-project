#pragma once

#include "Rect.h"
#include "RenderCommand.h"
#include "allegro5/color.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace Akr::Renderer {
class DrawRectAlphaOperation : public RenderCommand {
public:
  DrawRectAlphaOperation(ALLEGRO_COLOR color, Akr::Math::Rect const& rect, float alpha,
                         RenderCommandPriority const& _renderPriority = RenderCommand::RenderCommandPriority::DEFAULT)
      : RenderCommand(_renderPriority), color_(color), rect_(rect), alpha_(alpha){};

  void execute() override {
    al_draw_filled_rectangle(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h, al_map_rgba_f(color_.r, color_.g, color_.b, alpha_));
  }

private:
  DrawRectAlphaOperation() = delete;
  DrawRectAlphaOperation(DrawRectAlphaOperation const&) = delete;

  Akr::Math::Rect rect_;
  ALLEGRO_COLOR color_;
  float alpha_;
};
}  // namespace Akr::Renderer