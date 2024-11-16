#pragma once

#error "Timers.h should not be included in this project. It is WIP and not ready for use."

#include "Core.h"
#include <functional>
#include <map>
#include <chrono>
#include <allegro5/allegro.h> // Include Allegro 5 header

namespace Akr::Util {

class Timers {};

class FrequencyTimer : public Timers {
public:
  /*
   * A static template function that accepts a function and a frequency of times per second to call that function.
   * The function will track last frame (tick) it was called, and based on FPS it will call it again.
   *
   * @param function The function to call
   * @param frequency The frequency of times per second to call the function
   */
  template <typename RetVal>
  static RetVal CallFunctionAtFrequency(std::function<RetVal()> function, int frequency) {
    auto frameCount = Akr::Core::GetFrameCount();
    auto functionPtr = function.target<RetVal>; // Use 'template' keyword

    if (functionPtr == nullptr) {
      throw std::invalid_argument("Invalid function pointer");
    }

    auto& [lastFrame, duration] = functionMap_[functionPtr];

    if (frameCount - lastFrame >= duration) {
      lastFrame = frameCount;
      duration = static_cast<int>(1.0 / frequency / al_get_time());
      return function();
    }

    return RetVal();
  }

private:
  FrequencyTimer() = delete;
  ~FrequencyTimer() = delete;
  FrequencyTimer(FrequencyTimer const&) = delete;
  FrequencyTimer(FrequencyTimer&&) = delete;
  FrequencyTimer& operator=(FrequencyTimer const&) = delete;
  FrequencyTimer& operator=(FrequencyTimer&&) = delete;

  using FunctionKey = void(*)();
  static inline std::map<FunctionKey, std::pair<int, int>> functionMap_; // Map to store last frame and duration
};

}  // namespace Akr::Util