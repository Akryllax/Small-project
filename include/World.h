#pragma once

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"
#include <memory>

namespace Akr {
class World {
  b2World world;
  b2Vec2 gravity;

 public:
  World() : world(gravity) { this->gravity = b2Vec2(0.0, 10.0); };

  b2World& getBox2DWorld() { return this->world; }
};
}  // namespace Akr