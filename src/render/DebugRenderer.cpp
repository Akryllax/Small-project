#include "DebugRenderer.h"
#include "AllegroManager.h"
#include "DrawArrowOperation.h"
#include "DrawTextCommand.h"
#include "DrawCrossOperation.h"
#include "CompositeRenderCommand.h"

namespace Akr::Renderer {

void DebugRenderer::Initialize() {
  // Initialize
}

void DebugRenderer::setDefaultFont(ALLEGRO_FONT* _font) {
  //TODO
}

void DebugRenderer::addCommand(std::shared_ptr<RenderCommand> cmd) {
  commands.emplace(cmd);
}

std::shared_ptr<Renderer::RenderCommand> DebugRenderer::GenerateRenderCommand() {
  spdlog::trace("[DebugRenderer] DebugRenderer::GenerateRenderCommand()");

  auto compositeCommand = std::make_shared<CompositeRenderComand>();
  compositeCommand->QueueCommands(commands);

  return compositeCommand;
}

void DebugRenderer::DrawArrowDebug(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color) {
  addCommand(std::make_shared<DrawArrowCommand>(origin, destination, color));
}

void DebugRenderer::DrawTextDebug(std::string_view targetString, b2Vec2 screenSpacePosition, ALLEGRO_COLOR color) {
  spdlog::trace("[DebugRenderer] DebugRenderer::DrawText");
  addCommand(std::make_shared<DrawTextCommand>(targetString, screenSpacePosition, Akr::AllegroManager::mainFont, color));
}

void DebugRenderer::DrawCross(b2Vec2 const& _position, ALLEGRO_COLOR _color,
                              Akr::Renderer::RenderCommand::RenderCommandPriority const& _renderPriority) {
  spdlog::trace("[DebugRenderer] DebugRenderer::DrawCross");
  addCommand(std::make_shared<DrawCrossCommand>(_position, _color, _renderPriority));
}

}  // namespace Akr::Renderer
