#include "RendererLayer.h"
#include <spdlog/spdlog.h>  // Assuming you're using spdlog for logging

namespace Akr {
void RendererLayer::Tick(std::chrono::milliseconds const& delta) {
  spdlog::trace("[RenderLayer] RendererLayer::Tick()");

  // Generate render commands for registered renderables
  for (auto& renderable : renderables_) {
    if (renderable) {
      auto renderCommand = renderable->GenerateRenderCommand();
      if (renderCommand) {
        AddMainRenderCommand(renderCommand);
      }
    }
  }

  // Generate render commands for registered renderable pointers
  for (auto* renderableIt : purePtrRenderables_) {
    if (renderableIt) {
      auto renderCommand = renderableIt->GenerateRenderCommand();
      if (renderCommand) {
        AddMainRenderCommand(renderCommand);
      }
    }
  }

  // Generate render commands for UI registered renderable pointers
  for (auto* renderableUIIt : pureUIPtrRenderables_) {
    if (renderableUIIt) {
      auto renderCommand = renderableUIIt->GenerateRenderCommand();
      if (renderCommand) {
        AddMainRenderCommand(renderCommand);
      }
    }
  }


  // Add late render command from debug renderer
  AddLateRenderCommand(debugRenderer_.GenerateRenderCommand());
  AddLateRenderCommand(uiRenderer_.GenerateRenderCommand());

  // Perform rendering
  renderer_.render();
}

void RendererLayer::RegisterRenderable(std::shared_ptr<Akr::IRenderable> _renderable) {
  spdlog::trace("[RenderLayer] RendererLayer::RegisterRenderable()");
  renderables_.push_back(_renderable);
}

void RendererLayer::RegisterRenderablePtr(Akr::IRenderable* _renderablePtr) {
  spdlog::trace("[RenderLayer] RendererLayer::RegisterRenderable()");
  if (_renderablePtr) purePtrRenderables_.push_back(_renderablePtr);
}

void RendererLayer::RegisterUIRenderablePtr(Akr::IRenderable* _renderablePtr) {
  spdlog::trace("[RenderLayer] RendererLayer::RegisterUIRenderablePtr()");
  if (_renderablePtr) pureUIPtrRenderables_.push_back(_renderablePtr);
}

void RendererLayer::AddEarlyRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {
  spdlog::trace("[RenderLayer] RendererLayer::AddEarlyRenderCommand()");
  renderer_.addEarlyRenderCommand(command);
}

void RendererLayer::AddMainRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {
  spdlog::trace("[RenderLayer] RendererLayer::AddMainRenderCommand()");
  renderer_.addMainRenderCommand(command);
}

void RendererLayer::AddLateRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {
  spdlog::trace("[RenderLayer] RendererLayer::AddLateRenderCommand()");
  renderer_.addLateRenderCommand(command);
}

}  // namespace Akr
