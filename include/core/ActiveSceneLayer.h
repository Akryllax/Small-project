#pragma once

#include "DataLayer.h"
#include "Scene.h"
#include <memory>


namespace Akr {
  /*
   * ActiveSceneLayer is a DataLayer that holds the active scene.  It is responsible for ticking the active scene.
   * It is a DataLayer to circunvent the Core/CoreManager circular dependency.
   */
class ActiveSceneLayer : public DataLayer {
protected:
  std::shared_ptr<Akr::Game::Scene> activeScene_ = nullptr;

public:
  void Tick(std::chrono::milliseconds const& delta) override {
    spdlog::trace("[LocationLayer] Tick()");
    if (activeScene_) {
      activeScene_->Tick(delta);
    }
  }
  void SetActiveScene(std::shared_ptr<Akr::Game::Scene> scene) { activeScene_ = scene; }
  std::shared_ptr<Akr::Game::Scene> GetActiveScene() { return activeScene_; }
};
}  // namespace Akr