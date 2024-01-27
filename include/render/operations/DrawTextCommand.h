#pragma once

#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include "spdlog.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <string>

namespace Akr::Renderer {
class DrawTextCommand : public RenderCommand {
public:
  DrawTextCommand(std::string_view _targetString, b2Vec2 _screenSpacePosition, ALLEGRO_FONT* _font,
                  ALLEGRO_COLOR _color)
      : targetString(_targetString), screenSpacePosition(_screenSpacePosition), font(_font), color(_color) {}

  void execute() override {
    if (font) {
      al_draw_text(font, color, screenSpacePosition.x, screenSpacePosition.y, ALLEGRO_ALIGN_LEFT, targetString.data());
    } else {
      spdlog::error("[DrawTextCommand] Error: Font not loaded");
    }
  }

private:
  std::string targetString;
  b2Vec2 screenSpacePosition;
  ALLEGRO_FONT* font;
  ALLEGRO_COLOR color;
};
} // namespace Akr::Renderer