#pragma once

#include "RenderCommand.h"
#include "Resource.h"
#include <memory>

namespace Akr {
class IRenderable {
public:
  IRenderable();
  virtual ~IRenderable() = default;

  [[deprecated("SetBitmapResource is deprecated. Use RendererCommand generator instead.")]]
  inline void setBitmapResource(std::shared_ptr<BitmapResource> resource)
  {
    this->bitmapResource = resource;
  }

  [[deprecated("GetBitmapResource is deprecated. Use RendererCommand generator instead.")]]
  inline std::shared_ptr<BitmapResource>
  GetBitmapResource() const
  {
    return bitmapResource;
  }

  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() = 0;

  [[deprecated("Please use the RenderCommand flow")]] virtual void render(){};

private:
  std::shared_ptr<BitmapResource> bitmapResource;

  IRenderable(const IRenderable&) = delete;
  IRenderable& operator=(const IRenderable&) = delete;
};
}  // namespace Akr