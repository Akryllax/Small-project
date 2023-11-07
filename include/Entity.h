#pragma once

#include "Core.h"
#include "UniqueIdentifier.h"

namespace Akr {
class NamedLayer;
class Entity {
 public:
  Entity(UniqueIdentifier identifier) : identifier(identifier) {}

 public:
  const UniqueIdentifier identifier;
};
}  // namespace Akr