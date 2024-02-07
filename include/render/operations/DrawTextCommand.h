#pragma once

#include "Rect.h"
#include "RenderCommand.h"
#include "allegro5/allegro_font.h"
#include "box2d/b2_math.h"
#include "spdlog/spdlog.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <string_view>

namespace Akr::Renderer {
class DrawTextCommand : public RenderCommand {
public:
  DrawTextCommand(std::string_view _targetString, b2Vec2 _screenSpacePosition, ALLEGRO_FONT* _font,
                  ALLEGRO_COLOR _color, int allignment = ALLEGRO_ALIGN_LEFT)
      : targetString_(_targetString), screenSpacePosition_(_screenSpacePosition), font_(_font), color_(_color), allignment_{allignment} {}

  void execute() override {
    if (font_) {
      al_draw_text(font_, color_, screenSpacePosition_.x, screenSpacePosition_.y, allignment_, targetString_.data());
      spdlog::trace("[DrawTextCommand] Drawing '{}' at x:{}, y:{}", targetString_, screenSpacePosition_.x, screenSpacePosition_.y);
    } else {
      spdlog::error("[DrawTextCommand] Error: Font not loaded");
    }
  }

  // Function to calculate the size and position of the text within the button
  static inline Math::Rect CalculateTextRect(ALLEGRO_FONT* font, std::string const& text) {
    return Math::Rect{static_cast<float>(al_get_text_width(font, text.c_str())),
                      static_cast<float>(al_get_font_line_height(font))};
  }

  std::string targetString_;
  b2Vec2 screenSpacePosition_;
  ALLEGRO_FONT* font_;
  ALLEGRO_COLOR color_;
  int allignment_;
};
}  // namespace Akr::Renderer