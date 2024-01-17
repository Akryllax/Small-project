#include "DebugRenderer.h"
#include "IRenderable.h"
#include "PhysicsLayer.h"
#include "RigidBody.h"
#include "bitmap_draw.h"
#include "box2d/b2_body.h"
#include "spdlog.h"
#include <allegro5/allegro.h>
#include <cassert>
#include <memory>

namespace Akr {
class TestShip : public RigidBody, public IRenderable {
  b2BodyDef starshipDef;

public:
  TestShip(std::string const& name) : RigidBody(name, &(Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld())) {
    starshipDef.type = b2_dynamicBody;
    setBitmapResource(std::make_shared<BitmapResource>("1.png"));
    GetBitmapResource()->load();
    assert(body);
  }

  ~TestShip() override = default;

  void Render() override {
    spdlog::trace("[TestShip] Rendering TestShip (Name: {})", this->name);

    spdlog::info("rendering test ship, at pos: ({},{}), bitmap addr: {}", this->GetBody()->GetPosition().x,
                 this->GetBody()->GetPosition().y, GetBitmapResource() != nullptr);

    ALLEGRO_BITMAP* bitmap = GetBitmapResource()->getBitmap();
    float const cx = al_get_bitmap_width(bitmap) / 2.0f;   // X coordinate of the center of the bitmap
    float const cy = al_get_bitmap_height(bitmap) / 2.0f;  // Y coordinate of the center of the bitmap

    al_draw_rotated_bitmap(bitmap, cx, cy, this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y,
                           this->GetBody()->GetAngle(), 0);

    Akr::DebugRenderer::DrawArrow(this->GetBody()->GetPosition(),
                                  this->GetBody()->GetPosition() + this->GetBody()->GetLinearVelocity());
  }
};

}  // namespace Akr
