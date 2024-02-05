#pragma once

#include <random>

namespace Akr::Math {

class Utils {
public:
  static float getRandomInRange(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
  }
};
}  // namespace Akr::Math