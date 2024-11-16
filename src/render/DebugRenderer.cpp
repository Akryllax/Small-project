#include "DebugRenderer.h"
#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "DrawArrowOperation.h"
#include "DrawBoundingBoxCommand.h"
#include "DrawCrossOperation.h"
#include "DrawTextCommand.h"

namespace Akr::Renderer {

void DebugRenderer::Initialize() {
  // Initialize
}

void DebugRenderer::setDefaultFont(ALLEGRO_FONT* _font) {
  // TODO
}

void DebugRenderer::addCommand(std::shared_ptr<RenderCommand> cmd) { commands_.emplace(cmd); }

std::shared_ptr<Renderer::RenderCommand> DebugRenderer::GenerateRenderCommand() {
  spdlog::trace("[DebugRenderer] DebugRenderer::GenerateRenderCommand()");

  auto compositeCommand = std::make_shared<CompositeRenderComand>();
  compositeCommand->QueueCommands(commands_);

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

void DebugRenderer::DrawBoundingBox(Math::Rect const& _rect, ALLEGRO_COLOR _color,
                                    Akr::Renderer::RenderCommand::RenderCommandPriority const& _renderPriority) {
  spdlog::trace("[DebugRenderer] DebugRenderer::DrawBoundingBox");
  addCommand(std::make_shared<DrawBoundingBoxCommand>(_rect, _color, _renderPriority));
}

void DebugRenderer::SelectRenderer(DebugRenderer* _renderer) {
  if (_renderer != nullptr) {
    selectedRenderer_ = _renderer;
    spdlog::trace("[DebugRenderer] Renderer selected successfully.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to select renderer: _renderer is nullptr.");  // Log failure
  }
}

void DebugRenderer::DrawArrowStatic(b2Vec2 const& origin, b2Vec2 const& destination, ALLEGRO_COLOR color) {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->DrawArrowDebug(origin, destination, color);
    spdlog::trace("[DebugRenderer] Arrow drawn from origin to destination.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to draw arrow: selectedRenderer_ is nullptr.");  // Log failure
  }
}

void DebugRenderer::DrawTextStatic(std::string_view targetString, b2Vec2 screenSpacePosition, ALLEGRO_COLOR color) {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->DrawTextDebug(targetString, screenSpacePosition, color);
    spdlog::trace("[DebugRenderer] Text drawn at screen space position.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to draw text: selectedRenderer_ is nullptr.");  // Log failure
  }
}

void DebugRenderer::DrawCrossStatic(b2Vec2 const& _position, ALLEGRO_COLOR _color,
                                    RenderCommand::RenderCommandPriority const& _renderPriority) {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->DrawCross(_position, _color, _renderPriority);
    spdlog::trace("[DebugRenderer] Cross drawn at position.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to draw cross: selectedRenderer_ is nullptr.");  // Log failure
  }
}

void DebugRenderer::DrawBoundingBoxStatic(Math::Rect const& _rect, ALLEGRO_COLOR _color,
                                          RenderCommand::RenderCommandPriority const& _renderPriority) {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->DrawBoundingBox(_rect, _color, _renderPriority);
    spdlog::trace("[DebugRenderer] Bounding box drawn.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to draw bounding box: selectedRenderer_ is nullptr.");  // Log failure
  }
}

void DebugRenderer::AddCommandStatic(std::shared_ptr<RenderCommand> _command) {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->addCommand(_command);
    spdlog::trace("[DebugRenderer] Render command added.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to add render command: selectedRenderer_ is nullptr.");  // Log failure
  }
}

void DebugRenderer::GenerateRenderCommandStatic() {
  if (selectedRenderer_ != nullptr) {
    selectedRenderer_->GenerateRenderCommand();
    spdlog::trace("[DebugRenderer] Render command generated.");  // Log success
  } else {
    spdlog::error("[DebugRenderer] Failed to generate render command: selectedRenderer_ is nullptr.");  // Log failure
  }
}

}  // namespace Akr::Renderer
