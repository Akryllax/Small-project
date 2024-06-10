#pragma once

#include "Rect.h"
#include "RenderCommand.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "box2d/b2_math.h"
#include <memory>
#include <queue>
#include <string_view>

namespace Akr::Renderer {

/**
 * @brief DebugRenderer class for drawing debug elements.
 */
class DebugRenderer {
public:
  DebugRenderer() = default;
  virtual ~DebugRenderer()  = default;

  void Initialize();
  void setDefaultFont(ALLEGRO_FONT* _font);
  void addCommand(std::shared_ptr<RenderCommand> cmd);
  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand();

  // functions to create render operations
  void DrawArrowDebug(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color = al_map_rgb(255, 0, 0));
  void DrawTextDebug(std::string_view targetString, b2Vec2 screenSpacePosition,
                ALLEGRO_COLOR color = al_map_rgb(255, 255, 255));
  void DrawCross(b2Vec2 const& _position, ALLEGRO_COLOR _color = al_map_rgb(255, 0, 0),
                 Akr::Renderer::RenderCommand::RenderCommandPriority const& _renderPriority =
                     Akr::Renderer::RenderCommand::RenderCommandPriority::DEFAULT);

  void DrawBoundingBox(Math::Rect const& _rect, ALLEGRO_COLOR _color = al_map_rgb(255, 0, 0),
                       Akr::Renderer::RenderCommand::RenderCommandPriority const& _renderPriority =
                           Akr::Renderer::RenderCommand::RenderCommandPriority::DEFAULT);

private:
  inline static std::queue<std::shared_ptr<RenderCommand>> commands;
};

}  // namespace Akr::Renderer
