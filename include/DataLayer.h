#pragma once

#include "ITickable.h"
#include "spdlog/spdlog.h"

namespace Akr {
class DataLayer : public ITickable {
 public:
  constexpr static size_t EXEC_PRIORITY = 1;
  DataLayer() = default;
  virtual ~DataLayer() = default;

  virtual void Initialize(){};

  void Tick(std::chrono::milliseconds const delta) override {};
  virtual void Kill(){};
};
}  // namespace Akr
