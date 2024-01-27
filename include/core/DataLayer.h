#pragma once

#include "ITickable.h"

namespace Akr {
class DataLayer : public ITickable {
public:
  constexpr static size_t EXEC_PRIORITY = 100;
  DataLayer() = default;
  virtual ~DataLayer() = default;

  virtual void Initialize(){};

  void Tick(std::chrono::milliseconds const delta) override{};
  virtual void Kill(){};
  virtual size_t GetExecPriority() const { return EXEC_PRIORITY; }

private:
  DataLayer& operator=(DataLayer const&) = delete;
  DataLayer(DataLayer const&) = delete;
};
} // namespace Akr
