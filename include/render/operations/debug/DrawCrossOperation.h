#pragma once

#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

namespace Akr::Renderer {

class DrawCrossCommand : public RenderCommand {
private:
    b2Vec2 position;
    ALLEGRO_COLOR color;

public:
    // Constructor with default color red
    DrawCrossCommand(b2Vec2 const& _position,
                     ALLEGRO_COLOR _color = al_map_rgb(255, 0, 0), // Default color: Red
                     RenderCommandPriority const& _renderPriority = RenderCommandPriority::DEFAULT)
        : RenderCommand(_renderPriority), position(_position), color(_color) {}

    void execute() override {
        constexpr float crossSize = 10.0f; // Size of the cross arms

        // Draw horizontal line
        al_draw_line(position.x - crossSize, position.y, position.x + crossSize, position.y, color, 2.0);

        // Draw vertical line
        al_draw_line(position.x, position.y - crossSize, position.x, position.y + crossSize, color, 2.0);
    }
};

} // namespace Akr::Renderer
