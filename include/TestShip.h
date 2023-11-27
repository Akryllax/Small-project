#include "IRenderable.h"
#include "PhysicsLayer.h"
#include "RigidBody.h"
#include "bitmap_draw.h"
#include <allegro5/allegro.h>
#include <cassert>
#include <memory>

namespace Akr {
class TestShip : public RigidBody, public IRenderable {
  b2BodyDef starshipDef;

 public:
  TestShip(std::string const& name)
      : RigidBody(Akr::Core::GetInstance().GetDataLayer<Akr::PhysicsLayer>()->GetBox2DWorld().CreateBody(&starshipDef),
                  name) {
    bitmapResource = std::make_shared<BitmapResource>("1.png");
    bitmapResource->load();
    assert(body);
  }

 public:
  ~TestShip() override = default;

 public:
  void Render() override {
    al_draw_bitmap(bitmapResource->getBitmap(), this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y, 0);
  }
};

}  // namespace Akr
