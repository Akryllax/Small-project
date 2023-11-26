#include "Resource.h"
#include <memory>

namespace Akr {
class IRenderable {
 protected:
  std::shared_ptr<BitmapResource> bitmapResource;
 public:
  IRenderable() = default;
  virtual ~IRenderable() = default;

  virtual void Render() = 0;
};
}  // namespace Akr
