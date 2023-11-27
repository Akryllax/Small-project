#pragma once

#include "DataLayer.h"
#include "World.h"
#include <cassert>

namespace Akr {
class PhysicsLayer : public DataLayer {
 public:
  Akr::World world;
  void Tick(std::chrono::milliseconds const delta) override {
    this->GetBox2DWorld().Step(static_cast<float>(delta.count()) * 0.001f, 6, 2);
  }

  b2World& GetBox2DWorld() { return this->world.GetBox2DWorld(); }
};
}  // namespace Akr