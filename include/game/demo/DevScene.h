#pragma once

#include "Scene.h"
#include "TestShip.h"
#include "UIRectangle.h"
#include <array>
#include <memory>

namespace Akr::Game {

class DevScene : public Scene {
public:
  void OnLoad() override;
  void OnSave() override;
  void OnStart() override;
  void OnUnload() override;
  void Tick(const std::chrono::milliseconds& delta) override;

  std::array<std::shared_ptr<TestShip>, 10> ships;
  UI::UIRectangle rect{0, 0, 100, 100, al_map_rgb(255, 0, 0), 1.0f};
};
}  // namespace Akr::Game