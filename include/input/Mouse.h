#include "ITickable.h"
#include "allegro5/allegro.h"
#include <chrono>
#include <cstddef>

namespace Akr::Input {
class Mouse : public ITickable {
  ALLEGRO_MOUSE_STATE state;
  ALLEGRO_MOUSE_STATE previousState;

public:
  struct INPUT_MOUSE_STATE : public ALLEGRO_MOUSE_STATE {
        // Keep existing frame counter
    size_t FRAME_COUNT;

    // Add useful mouse state info (aligned for performance)
    bool is_dragging;           // 1 byte
    bool was_pressed;           // 1 byte
    bool was_released;          // 1 byte
    uint8_t button_count;       // 1 byte to complete alignment

    float drag_start_x;        // 4 bytes
    float drag_start_y;        // 4 bytes
    float drag_delta_x;        // 4 bytes
    float drag_delta_y;        // 4 bytes
  };

  enum class Button { LEFT = 1, RIGHT = 2, MIDDLE = 3, BUTTON4 = 4, BUTTON5 = 5, BUTTON6 = 6, BUTTON7 = 7, BUTTON8 = 8 };

  Mouse();
  ~Mouse();

  void Tick(std::chrono::milliseconds const& delta) override {}
  bool isButtonPressed(int button) {}
  bool isButtonReleased(int button) {}
  bool isButtonDown(int button) {}
  bool isButtonUp(int button) {}
  int getX() {}
  int getY() {}
  int getZ() {}
  int getDZ() {}
  int getDW() {}
};
}  // namespace Akr::Input