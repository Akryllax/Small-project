#include "Rect.h"
#include "UIElement.h"
#include "allegro5/color.h"
#include <cstdint>

namespace Akr::UI {

/**
 * @brief A panel is a container that can hold other UI elements.
 */
class Panel : public UIElement {
public:
  Panel(uint16_t id = 0) : UIElement(Type::PANEL, id) {}

  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override;

private:
  ALLEGRO_COLOR mainColor;
  ALLEGRO_COLOR borderColor;
  int borderWidth;
  Akr::Math::Rect panelRect;
};

} // namespace Akr::UI
