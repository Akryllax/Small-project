#pragma once
#include "spdlog/spdlog.h"
#include <chrono>


class ITickable {
public:
  virtual void Start() {};
  virtual void Stop() {};
  virtual void Tick(std::chrono::milliseconds const& delta) {};
  virtual ~ITickable() = default;
};