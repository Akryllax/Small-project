#include "GameTimerLayer.h"

void Akr::Game::Timers::Initialize() {
  spdlog::trace("[LocationLayer] Initialize¡()");
};

void Akr::Game::Timers::Tick(std::chrono::milliseconds const& delta) {
  auto frameCount = Akr::Core::GetFrameCount();
  spdlog::trace("[LocationLayer] Tick()");
};
