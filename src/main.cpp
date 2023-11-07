#include "Core.h"
#include "LocationLayer.h"
#include "NamedLayer.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

int _initCore(Akr::Core& coreInstance) {
  coreInstance.AddDataLayer(new Akr::NameLayer());
  coreInstance.AddDataLayer(new Akr::LocationLayer());
  coreInstance.AddDataLayer(new Akr::NameLayer());

  return 0;
}

int _coreLoop(Akr::Core& coreInstance, const std::chrono::milliseconds delta) {
  coreInstance.Tick(delta);

  return 0;
}

int main(int argc, char** argv) {
  Akr::Core coreInstance;
  _initCore(coreInstance);

  auto applicationEpoch = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds targetFrameTime(1000 / 30);  // 30 FPS

  while (true) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds lastTick =
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                              applicationEpoch);

    // Call the core loop only when it's time for the next frame
    if (lastTick >= targetFrameTime) {
      _coreLoop(coreInstance, lastTick);

      // Print frame count and time
      auto now = std::chrono::system_clock::now();
      auto now_time = std::chrono::system_clock::to_time_t(now);
      auto timeinfo = std::localtime(&now_time);
      std::cout << "[" << std::put_time(timeinfo, "%T")
                << " | FrameNumber: " << coreInstance.GetFrameCount() << "]" << std::endl;

      // Update the applicationEpoch to the time of the last frame
      applicationEpoch = currentTime;
    }

    // Sleep for the remaining time until the next frame
    std::this_thread::sleep_for(targetFrameTime - lastTick);
  }

  std::cout << "Hello, dataGen!" << std::endl;
  return 0;
}
