#pragma once

#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_font.h>
#include <string_view>

namespace Akr {

/**
 * @brief DebugRenderer class for drawing debug elements.
 */
class DebugRenderer {
public:
    /**
     * @brief Draws an arrow from the origin to the destination.
     * @param origin The starting point of the arrow.
     * @param destination The ending point of the arrow.
     * @param color The color of the arrow (default is red).
     */
    static void DrawArrow(b2Vec2 const& origin, b2Vec2 const& destination,
                          const ALLEGRO_COLOR& color = al_map_rgb(255, 0, 0)) {
        // Arrow shaft
        al_draw_line(origin.x, origin.y, destination.x, destination.y, color, 2.0);

        // Arrowhead (triangle)
        auto angle = atan2(destination.y - origin.y, destination.x - origin.x);
        auto arrowSize = 10.0; // Adjust the arrowhead size as needed

        auto arrowX1 = static_cast<float>(destination.x - arrowSize * cos(angle - ALLEGRO_PI / 6.0f));
        auto arrowY1 = static_cast<float>(destination.y - arrowSize * sin(angle - ALLEGRO_PI / 6.0f));

        auto arrowX2 = static_cast<float>(destination.x - arrowSize * cos(angle + ALLEGRO_PI / 6.0f));
        auto arrowY2 = static_cast<float>(destination.y - arrowSize * sin(angle + ALLEGRO_PI / 6.0f));

        al_draw_filled_triangle(destination.x, destination.y, arrowX1, arrowY1, arrowX2, arrowY2, color);
    }

    /**
     * @brief Draws text at the specified screen space position.
     * @param targetString The string to be drawn.
     * @param screenSpacePosition The position where the text will be drawn.
     * @param size The size of the text (default is -1, which means using the default size).
     * @param color The color of the text (default is white).
     */
    static void DrawText(std::string_view targetString, b2Vec2 screenSpacePosition, int size = -1,
                         const ALLEGRO_COLOR& color = al_map_rgb(255, 255, 255)) {
        static ALLEGRO_FONT* font = al_create_builtin_font(); // Use built-in font, replace with your own if needed
        if (!font) {
            // Handle font creation failure
            return;
        }

        al_draw_text(font, color, screenSpacePosition.x, screenSpacePosition.y, ALLEGRO_ALIGN_LEFT, targetString.data());
    }
};

} // namespace Akr
