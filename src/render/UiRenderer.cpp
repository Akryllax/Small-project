#include "UiRenderer.h"
#include <spdlog/spdlog.h>
#include "CompositeRenderCommand.h"

namespace Akr::Renderer {

void UiRenderer::Initialize() {
  // Initialize
}

void UiRenderer::setDefaultFont(ALLEGRO_FONT* _font) {
  // TODO
}

void UiRenderer::addCommand(std::shared_ptr<RenderCommand> cmd) { commands.emplace(cmd); }

std::shared_ptr<Renderer::RenderCommand> UiRenderer::GenerateRenderCommand() {
  spdlog::trace("[UiRenderer] UiRenderer::GenerateRenderCommand()");

  auto compositeCommand = std::make_shared<CompositeRenderComand>();
  compositeCommand->QueueCommands(commands);

  return compositeCommand;
}
}  // namespace Akr::Renderer
