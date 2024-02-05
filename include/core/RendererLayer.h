#pragma once

#include "CoreRenderer.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IRenderable.h"
#include "RenderCommand.h"
#include <memory>
#include <vector>

namespace Akr {

class RendererLayer : public DataLayer {
public:
  inline Renderer::DebugRenderer& GetDebugRenderer() { return debugRenderer_; }
  inline Renderer::CoreRenderer& GetCoreRenderer() { return renderer_; }

  void Tick(std::chrono::milliseconds const& delta) override {
    spdlog::trace("[RenderLayer] RendererLayer::Tick()");

    for(auto renderable : renderables_)
    {
      AddMainRenderCommand(renderable->GenerateRenderCommand());
    }

    AddLateRenderCommand(debugRenderer_.GenerateRenderCommand());

    renderer_.render();
  }

  //IRenderables managment
  void RegisterRenderable(std::shared_ptr<Akr::IRenderable> _renderable)
  {
    spdlog::trace("[RenderLayer] RendererLayer::RegisterRenderable()");
    renderables_.push_back(_renderable);
  }

  // CoreRenderer interface
  void AddEarlyRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {
    spdlog::trace("[RenderLayer] RendererLayer::AddEarlyRenderCommand()");
    renderer_.addEarlyRenderCommand(command);
  }
  void AddMainRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {

    spdlog::trace("[RenderLayer] RendererLayer::AddMainRenderCommand()");
    renderer_.addMainRenderCommand(command);
  }
  void AddLateRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command) {

    spdlog::trace("[RenderLayer] RendererLayer::AddLateRenderCommand()");
    renderer_.addLateRenderCommand(command);
  }

private:
  Akr::Renderer::CoreRenderer renderer_;
  Akr::Renderer::DebugRenderer debugRenderer_;
  std::vector<std::shared_ptr<IRenderable>> renderables_;
};
} // namespace Akr
