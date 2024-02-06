#pragma once

#include "DataLayer.h"
#include "ITickable.h"
#include "Location.h"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Akr {
class LocationLayer : public DataLayer {
protected:
  std::unordered_map<std::string, Location> locationVector;

  void Tick(std::chrono::milliseconds const& delta) override { spdlog::trace("[LocationLayer] Tick()"); }
};
}  // namespace Akr