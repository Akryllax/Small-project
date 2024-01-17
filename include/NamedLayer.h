#pragma once

#include "DataLayer.h"
#include "Entity.h"
#include "spdlog/spdlog.h"
#include <vector>

namespace Akr {
class NamedLayer : public DataLayer, public std::vector<Entity> {
public:
  void Tick(std::chrono::milliseconds const delta) override { spdlog::trace("NamedLayer::Tick()"); }
};
}  // namespace Akr
