#pragma once

#include "UniqueIdentifier.h"

namespace Akr {
class Entity {
 public:
  Entity(UniqueIdentifier identifier) : identifier(identifier) {}

 public:
  const UniqueIdentifier identifier;
};
}  // namespace Akr