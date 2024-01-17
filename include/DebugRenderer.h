#include "box2d/b2_math.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

namespace Akr {
class DebugRenderer {
public:
  static void DrawArrow(b2Vec2 const& origin, b2Vec2 const& destination,
                        const ALLEGRO_COLOR& color = al_map_rgb(255, 0, 0)) {
    // Arrow shaft
    al_draw_line(origin.x, origin.y, destination.x, destination.y, color, 2.0);

    // Arrowhead (triangle)
    float angle = atan2(destination.y - origin.y, destination.x - origin.x);
    float arrowSize = 10.0;  // Adjust the arrowhead size as needed

    float arrowX1 = static_cast<float>(destination.x - arrowSize * cos(angle - ALLEGRO_PI / 6.0f));
    float arrowY1 = static_cast<float>(destination.y - arrowSize * sin(angle - ALLEGRO_PI / 6.0f));

    float arrowX2 = static_cast<float>(destination.x - arrowSize * cos(angle + ALLEGRO_PI / 6.0f));
    float arrowY2 = static_cast<float>(destination.y - arrowSize * sin(angle + ALLEGRO_PI / 6.0f));

    al_draw_filled_triangle(destination.x, destination.y, arrowX1, arrowY1, arrowX2, arrowY2, color);
  }
};
}  // namespace Akr
