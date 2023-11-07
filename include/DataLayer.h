#pragma once

#include "ITickable.h"

namespace Akr {
class DataLayer : public ITickable {
 public:
  DataLayer() = default;
  virtual ~DataLayer() = default;

  virtual void Initialize(){};
  
  void Tick(const std::chrono::milliseconds delta) override {
    std::cout << typeid(*this).name() << "::Tick()" << std::endl;
  };
  virtual void Kill(){};
};
}  // namespace Akr
