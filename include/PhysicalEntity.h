#pragma once

#include "Entity.h"
#include "Location.h"
#include "box2d/box2d.h"

namespace Akr {
class PhysicalEntity : public Entity {
 public:
  PhysicalEntity(std::string const& name) : Entity(name){};

 private:
  Location location_;

 public:
  Location& GetLocation() { return location_; }
};
}  // namespace Akr