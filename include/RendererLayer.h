#include "DataLayer.h"
#include "IRenderable.h"
#include <memory>
#include <vector>

namespace Akr {

class RendererLayer : public DataLayer {
public:
    void RegisterRenderable(std::shared_ptr<Akr::IRenderable> renderable) {
        this->renderables.push_back(renderable);
    }

    void Tick(std::chrono::milliseconds const delta) override {
      for(auto renderable : renderables)
      {
        renderable->Render();
      }
    }
private:
    std::vector<std::shared_ptr<Akr::IRenderable>> renderables;
};
}  // namespace Akr
