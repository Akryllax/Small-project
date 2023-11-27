#include "IRenderable.h"
#include "PhysicalEntity.h"
#include "UniqueIdentifier.h"
#include "bitmap_draw.h"
#include <allegro5/allegro.h>
#include <memory>

namespace Akr {
class TestShip : public PhysicalEntity, public IRenderable {
 public:
  TestShip(std::string const& name) : PhysicalEntity(name) {
    this->bitmapResource = std::make_shared<BitmapResource>("1.png");
    this->bitmapResource->load();
  };

 public:
  ~TestShip() override = default;

 public:
  void Render() override {
    al_draw_bitmap(bitmapResource->getBitmap(), this->GetLocation().getPosition().x,
                   this->GetLocation().getPosition().y, 0);
  }
};
}  // namespace Akr