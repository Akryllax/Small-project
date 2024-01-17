#include "IRenderable.h"
#include "PhysicsLayer.h"
#include "RigidBody.h"
#include "bitmap_draw.h"
#include "box2d/b2_body.h"
#include <allegro5/allegro.h>
#include <cassert>
#include <memory>

namespace Akr {
class TestShip : public RigidBody, public IRenderable {
  b2BodyDef starshipDef;

public:
  TestShip(std::string const& name)
      : RigidBody(name, &(Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld())) {
    starshipDef.type = b2_dynamicBody;
    setBitmapResource(std::make_shared<BitmapResource>("1.png"));
    GetBitmapResource()->load();
    assert(body);
  }

  ~TestShip() override = default;

  void Render() override {
    al_draw_bitmap(GetBitmapResource()->getBitmap(), this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y, 0);
  }
};

}  // namespace Akr
