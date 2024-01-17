#pragma once
#include <chrono>
#include "spdlog/spdlog.h"

class ITickable {
 public:
  virtual void Tick(const std::chrono::milliseconds delta) {};
};