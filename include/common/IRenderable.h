#pragma once

#include "Resource.h"
#include <memory>

namespace Akr {
class IRenderable {
private:
  std::shared_ptr<BitmapResource> bitmapResource;

public:
  IRenderable() = default;
  virtual ~IRenderable() = default;

  inline void setBitmapResource(std::shared_ptr<BitmapResource> resource) { this->bitmapResource = resource; }

  inline std::shared_ptr<BitmapResource> GetBitmapResource() const { return bitmapResource; }

  virtual void Render() = 0;
};
}  // namespace Akr