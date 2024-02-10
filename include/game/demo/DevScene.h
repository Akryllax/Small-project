#pragma once

#include "Scene.h"

namespace Akr::Game {

class DevScene : public Scene {
  public:
  void OnLoad() override;
  void OnSave() override;
};
}  // namespace Akr::Game