#pragma once

#include "RenderCommand.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "box2d/b2_math.h"
#include <algorithm>
#include <memory>
#include <queue>
#include <string_view>
#include <vector>

namespace Akr::Renderer {

/**
 * @brief UiRenderer class for drawing UI elements.
 */
class UiRenderer {
public:
  UiRenderer() = default;
  virtual ~UiRenderer()  = default;

  void Initialize();
  void setDefaultFont(ALLEGRO_FONT* _font);
  void addCommand(std::shared_ptr<RenderCommand> cmd);
  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand();

private:
  inline static std::queue<std::shared_ptr<RenderCommand>> commands;
};

}  // namespace Akr::Renderer
