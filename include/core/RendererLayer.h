#include "DataLayer.h"
#include "DebugRenderer.h"
#include "IRenderable.h"
#include <memory>
#include <vector>

namespace Akr {

class RendererLayer : public DataLayer {
public:
  void RegisterRenderable(std::shared_ptr<Akr::IRenderable> renderable) {
    spdlog::info("Registered renderable");
    this->renderables.push_back(renderable);
  }

  void Tick(std::chrono::milliseconds const delta) override {
    spdlog::trace("RendererLayer::Tick()");

    // spdlog::trace("[Renderer] -- START OF FRAME --");
    // spdlog::trace("[Renderer] Clearing screen");
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // spdlog::trace("[Renderer] Rendering all renderables");
    for (auto renderable : renderables) {
      renderable->Render();
    }

  // spdlog::trace("[Renderer] Flip buffers");
    Akr::Renderer::DebugRenderer::render();
    al_flip_display();  // Assuming double buffering

    // spdlog::trace("[Renderer] ## END OF FRAME ## ");
  }

private:
  std::vector<std::shared_ptr<Akr::IRenderable>> renderables;
};
}  // namespace Akr
