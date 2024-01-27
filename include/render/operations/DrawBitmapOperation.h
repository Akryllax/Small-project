#pragma once

#include "Rect.h"
#include "RenderCommand.h"
#include "bitmap.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_math.h"
#include "spdlog.h"
#include <allegro5/allegro.h>

namespace Akr::Renderer {
class DrawBitmapOperation : public RenderCommand {
public:
  DrawBitmapOperation(ALLEGRO_BITMAP* _targetBitmap, Akr::Math::Rect const& _bitmapRect, const RenderCommandPriority& _renderPriority = RenderCommand::RenderCommandPriority::DEFAULT)
      : RenderCommand(_renderPriority), bitmap_(_targetBitmap), rect_(_bitmapRect){};

  void execute() override {
    if (!bitmap_) {
      spdlog::error("[Renderer] Trying to draw an empty bitmap!");
      return;
    }

    float const cx = al_get_bitmap_width(bitmap_) / 2.0f;  // X coordinate of the center of the bitmap
    float const cy = al_get_bitmap_height(bitmap_) / 2.0f; // Y coordinate of the center of the bitmap

    al_draw_rotated_bitmap(bitmap_, cx, cy, rect_.x, rect_.y,
                           rect_.angle, 0);
  }

private:
  DrawBitmapOperation() = delete;
  Akr::Math::Rect rect_;
  ALLEGRO_BITMAP* bitmap_;
};
} // namespace Akr::Renderer