#pragma once

#include "ITickable.h"

namespace Akr {
class GameLayer : public ITickable {
public:
  constexpr static size_t EXEC_PRIORITY = 100;
  GameLayer() = default;
  ~GameLayer() override = default;

  virtual void Initialize(){};

  void Tick(std::chrono::milliseconds const& delta) override{};
  virtual void Kill(){};
  virtual size_t GetExecPriority() const { return EXEC_PRIORITY; }

private:
  GameLayer& operator=(GameLayer const&) = delete;
  GameLayer(GameLayer const&) = delete;
};
} // namespace Akr
