#pragma once

#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_font.h>
#include <string>
#include <string_view>
#include <queue>
#include <memory>
#include "DrawArrowOperation.h"
#include "DrawTextCommand.h"

namespace Akr::Renderer {

/**
 * @brief DebugRenderer class for drawing debug elements.
 */
class DebugRenderer {
private:
  inline static ALLEGRO_FONT* defaultFont = nullptr;
  inline static std::queue<std::shared_ptr<RenderCommand>> commands;

public:
  DebugRenderer() = delete;
  ~DebugRenderer() = delete;

  static void Initialize() { defaultFont = al_create_builtin_font(); }

  static void setDefaultFont(ALLEGRO_FONT* _font) { defaultFont = _font; }

  static void addCommand(RenderCommand* cmd) { commands.emplace(cmd); }

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

} // namespace Akr::Renderer
