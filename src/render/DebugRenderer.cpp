#include "DebugRenderer.h"
#include "AllegroManager.h"

namespace Akr::Renderer {

DebugRenderer::DebugRenderer() = default;

void DebugRenderer::Initialize() {
  // Initialize
}

void DebugRenderer::setDefaultFont(ALLEGRO_FONT* _font) {
  //TODO
}

void DebugRenderer::addCommand(std::shared_ptr<RenderCommand> cmd) {
  commands.emplace(cmd);
}

[[deprecated("Please, use the RenderCommand method, plz")]] void DebugRenderer::render() {
  while (!commands.empty()) {
    commands.front()->execute();
    commands.pop();
  }
}

std::shared_ptr<Renderer::RenderCommand> DebugRenderer::GenerateRenderCommand() {
  spdlog::trace("[DebugRenderer] DebugRenderer::GenerateRenderCommand()");

  auto compositeCommand = std::make_shared<CompositeRenderComand>();
  compositeCommand->QueueCommands(commands);

  return compositeCommand;
}

void DebugRenderer::DrawArrow(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color) {
  addCommand(std::make_shared<DrawArrowCommand>(origin, destination, color));
}

void DebugRenderer::DrawText(std::string_view targetString, b2Vec2 screenSpacePosition, ALLEGRO_COLOR color) {
  spdlog::trace("[DebugRenderer] DebugRenderer::DrawText");
  addCommand(std::make_shared<DrawTextCommand>(targetString, screenSpacePosition, Akr::Init::AllegroManager::mainFont, color));
}

void DebugRenderer::DrawCross(b2Vec2 const& _position, ALLEGRO_COLOR _color,
                              Akr::Renderer::RenderCommand::RenderCommandPriority const& _renderPriority) {
  spdlog::trace("[DebugRenderer] DebugRenderer::DrawCross");
  addCommand(std::make_shared<DrawCrossCommand>(_position, _color, _renderPriority));
}

}  // namespace Akr::Renderer
