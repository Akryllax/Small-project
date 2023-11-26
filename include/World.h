#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

namespace Akr {
class World {
  b2World world;
  b2Vec2 gravity;

 public:
  World() : gravity(0.0f, -10.0f), world(gravity){};

  b2World* getBox2DWorld() { return &this->world; }
};
}  // namespace Akr