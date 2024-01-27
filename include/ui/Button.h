#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_ttf.h>
#include <string>

class Button {
 public:
  Button(int x, int y, int width, int height, char const* label)
      : x(x), y(y), width(width), height(height), label(label) {
    pressed = false;
  }

  bool isMouseOver(int mouseX, int mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y &&
           mouseY <= y + height;
  }

  void draw() {
    al_draw_filled_rectangle(
        x, y, x + width, y + height,
        pressed ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 0, 0));
    al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255),
                 x + width / 2, y + height / 2, ALLEGRO_ALIGN_CENTRE, label.c_str());
  }

  void handleClick() {
    pressed = true;
    // Implement your action here when the button is clicked.
  }
  int x, y, width, height;
  std::string label;
  bool pressed;
  void release() { pressed = false; }
};