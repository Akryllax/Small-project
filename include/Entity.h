#pragma once

#include "Core.h"
#include <memory>

namespace Akr {
class NamedLayer;
class Entity {
 public:
  Entity(std::string const& identifier) : name(identifier){};

 public:
  std::string const name;
};
}  // namespace Akr