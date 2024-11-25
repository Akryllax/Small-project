#pragma once

#include "DataLayer.h"
#include "Scene.h"
#include "SimpleScene.h"
#include <memory>

namespace Akr {
/*
 * ActiveSceneLayer is a DataLayer that holds the active scene.  It is responsible for ticking the active scene.
 * It is a DataLayer to circunvent the Core/CoreManager circular dependency.
 */
class ActiveSceneLayer : public DataLayer {
public:
  void Tick(std::chrono::milliseconds const& delta) override {
    spdlog::trace("[LocationLayer] Tick()");
    if (simpleActiveScene_) {
      simpleActiveScene_->Tick(delta);
    } else if (activeScene_) {
      activeScene_->Tick(delta);
    }
  }
  void SetActiveScene(std::shared_ptr<Akr::Game::Scene> scene) { activeScene_ = scene; }
  std::shared_ptr<Akr::Game::Scene> GetActiveScene() { return activeScene_; }

  void SetsimpleActiveScene(std::shared_ptr<Akr::Game::SimpleScene> simpleScene) { simpleActiveScene_ = simpleScene; }

protected:
  std::shared_ptr<Akr::Game::Scene> activeScene_ = nullptr;
  std::shared_ptr<Akr::Game::SimpleScene> simpleActiveScene_ = nullptr;
};
}  // namespace Akr