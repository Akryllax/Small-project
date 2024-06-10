#pragma once

#include "DevScene.h"
#include "Scene.h"
#include "TestShip.h"
#include "UIRectangle.h"
#include "Panel.h"
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

  UI::Panel mainPanel = UI::Panel(1);
};
}  // namespace Akr::Game