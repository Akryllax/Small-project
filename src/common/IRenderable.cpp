#include "IRenderable.h"
#include "Core.h"
#include "RendererLayer.h"

namespace Akr {
IRenderable::IRenderable() {
  spdlog::trace("[IRenderable] IRenderable(), registering to RendererLayer.");
}

}  // namespace Akr