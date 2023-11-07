#pragma once

#include "Entity.h"
#include "Location.h"

namespace Akr {
class PhsysicalEntity : public Entity {
 public:
    PhsysicalEntity(UniqueIdentifier identifier) : Entity(identifier) {};
 private:
  Location location_;


  Location& GetLocation() { return location_; }
};
}  // namespace Akr