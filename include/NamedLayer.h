#pragma once

#include "DataLayer.h"
#include "Entity.h"
#include "UniqueIdentifier.h"
#include <iostream>  // Add this for std::cout
#include <map>
#include <vector>

namespace Akr {
class NamedLayer : public DataLayer, public std::vector<Entity> {
 public:
  void Tick(const std::chrono::milliseconds delta) override {
    std::cout << "NamedLayer" << "::Tick()" << std::endl;
  }
};
}  // namespace Akr
