#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "ITickable.h"
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Akr::Game {
class Timers : public DataLayer {
protected:
  template <typename T>
  struct Timer {
    std::chrono::milliseconds duration;
    std::chrono::milliseconds elapsed;
    bool active;
    std::function<T> callTarget;
  };

  std::unordered_map<std::string, std::chrono::milliseconds> timers;

  void Initialize() override;

  void Tick(std::chrono::milliseconds const& delta) override;
};  // namespace Akr
}  // namespace Akr::Game