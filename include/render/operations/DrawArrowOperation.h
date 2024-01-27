#pragma once

#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

namespace Akr::Renderer {
class DrawArrowCommand : public RenderCommand {
private:
  b2Vec2 origin;
  b2Vec2 destination;
  ALLEGRO_COLOR color;

public:
  DrawArrowCommand(b2Vec2 const& _origin, b2Vec2 const& _destination, ALLEGRO_COLOR _color)
      : origin(_origin), destination(_destination), color(_color) {}

  void execute(RenderCommandPriority const& renderPriority = RenderCommandPriority::DEFAULT) override {
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
} // namespace Akr::Renderer