#pragma once
#include <chrono>
#include <iostream>

class ITickable {
 public:
  virtual void Tick(const std::chrono::milliseconds delta) {
    std::cout << "ITickale" << std::endl;
  };
};