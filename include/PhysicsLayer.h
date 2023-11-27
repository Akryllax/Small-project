#include "DataLayer.h"
#include "World.h"

namespace Akr {
class PhysicsLayer : public DataLayer {
 public:
  Akr::World world;
  void Tick(std::chrono::milliseconds const delta) override {
    this->world.getBox2DWorld().Step(static_cast<float>(delta.count()) * 0.001f,
                                     6, 2);
  }
};
}  // namespace Akr