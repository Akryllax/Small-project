#pragma once

#include "CompositeRenderCommand.h"
#include "DrawArrowOperation.h"
#include "DrawTextCommand.h"
#include "IRenderable.h"
#include "RenderCommand.h"
#include "box2d/b2_math.h"
#include "spdlog.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_font.h>
#include <memory>
#include <queue>
#include <string_view>

namespace Akr::Renderer {

/**
 * @brief DebugRenderer class for drawing debug elements.
 */
class DebugRenderer : public IRenderable {
public:
  DebugRenderer() = default;
  ~DebugRenderer() = default;

  void Initialize() { defaultFont = al_create_builtin_font(); }

  void setDefaultFont(ALLEGRO_FONT* _font) { defaultFont = _font; }

  void addCommand(std::shared_ptr<RenderCommand> cmd) { commands.emplace(cmd); }

  [[deprecated("Please, use the RenderCommand method, plz")]] void render() override {
    while (!commands.empty()) {
      commands.front()->execute();
      commands.pop();
    }
  }

  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override {
    spdlog::trace("[DebugRenderer] DebugRenderer::GenerateRenderCommand()");

    auto compositeCommand = std::make_shared<CompositeRenderComand>();
    compositeCommand->QueueCommands(commands);

    return compositeCommand;
  };

  // functions to create render operations
  void DrawArrow(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color = al_map_rgb(255, 0, 0)) {
    addCommand(std::make_shared<DrawArrowCommand>(origin, destination, color));
  }

  void DrawText(std::string_view targetString, b2Vec2 screenSpacePosition,
                ALLEGRO_COLOR color = al_map_rgb(255, 255, 255)) {
    spdlog::trace("[DebugRenderer] DebugRenderer::DrawText");
    addCommand(std::make_shared<DrawTextCommand>(targetString, screenSpacePosition, defaultFont, color));
  }

private:
  inline static ALLEGRO_FONT* defaultFont = nullptr;
  inline static std::queue<std::shared_ptr<RenderCommand>> commands;
};

} // namespace Akr::Renderer
