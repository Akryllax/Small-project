#pragma once

#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_font.h>
#include <memory>
#include <queue>
#include <string>
#include <string_view>

namespace Akr {

/**
 * @brief DebugRenderer class for drawing debug elements.
 */
class DebugRenderer {
private:
  class DebugRenderCommand {
  public:
    virtual void execute() = 0;
    virtual ~DebugRenderCommand() = default;
  };

  class DrawArrowCommand : public DebugRenderCommand {
  private:
    b2Vec2 origin;
    b2Vec2 destination;
    ALLEGRO_COLOR color;

  public:
    DrawArrowCommand(b2Vec2 const& _origin, b2Vec2 const& _destination, ALLEGRO_COLOR _color)
        : origin(_origin), destination(_destination), color(_color) {}

    void execute() override {
      al_draw_line(origin.x, origin.y, destination.x, destination.y, color, 2.0);
      auto angle = atan2(destination.y - origin.y, destination.x - origin.x);
      auto arrowSize = 10.0;

      auto arrowX1 = static_cast<float>(destination.x - arrowSize * cos(angle - ALLEGRO_PI / 6.0f));
      auto arrowY1 = static_cast<float>(destination.y - arrowSize * sin(angle - ALLEGRO_PI / 6.0f));

      auto arrowX2 = static_cast<float>(destination.x - arrowSize * cos(angle + ALLEGRO_PI / 6.0f));
      auto arrowY2 = static_cast<float>(destination.y - arrowSize * sin(angle + ALLEGRO_PI / 6.0f));

      al_draw_filled_triangle(destination.x, destination.y, arrowX1, arrowY1, arrowX2, arrowY2, color);
    }
  };

  class DrawTextCommand : public DebugRenderCommand {
  private:
    std::string targetString;
    b2Vec2 screenSpacePosition;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;

  public:
    DrawTextCommand(std::string_view _targetString, b2Vec2 _screenSpacePosition, ALLEGRO_FONT* _font,
                    ALLEGRO_COLOR _color)
        : targetString(_targetString), screenSpacePosition(_screenSpacePosition), font(_font), color(_color) {}

    void execute() override {
      if (font) {
        al_draw_text(font, color, screenSpacePosition.x, screenSpacePosition.y, ALLEGRO_ALIGN_LEFT, targetString.data());
      }
    }
  };

  inline static ALLEGRO_FONT* defaultFont = nullptr;
  inline static std::queue<std::shared_ptr<DebugRenderCommand>> commands;

public:
  DebugRenderer() = delete;
  ~DebugRenderer() = delete;

  static void Initialize() { defaultFont = al_create_builtin_font(); }

  static void setDefaultFont(ALLEGRO_FONT* _font) { defaultFont = _font; }

  static void addCommand(DebugRenderCommand* cmd) { commands.emplace(cmd); }

  static void render() {
    while (!commands.empty()) {
      commands.front()->execute();
      commands.pop();
    }
  }

  // Static functions to create render operations

  static void DrawArrow(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color = al_map_rgb(255, 0, 0)) {
    addCommand(new DrawArrowCommand(origin, destination, color));
  }

  static void DrawText(std::string_view targetString, b2Vec2 screenSpacePosition,
                       ALLEGRO_COLOR color = al_map_rgb(255, 255, 255)) {
    addCommand(new DrawTextCommand(targetString, screenSpacePosition, defaultFont, color));
  }
};

} // namespace Akr
