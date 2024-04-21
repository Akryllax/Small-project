#include "CoreManager.h"
#include "ActiveSceneLayer.h"
#include "Configuration.h"
#include "Core.h"
#include "DebugConsole.h"
#include "GameLayer.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "RendererLayer.h"
#include "Scene.h"
#include "UIInputController.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace Akr {
int CoreManager::Initialize() {
  Akr::Configuration::load();
  Akr::Logger::Init();

  Akr::Core::GetInstance().AddDataLayer<Akr::GameLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::ActiveSceneLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::InputLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::LocationLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::NamedLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::PhysicsLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::RendererLayer>();

  //!DEBT Initialize the debug console, [nondiscard] is annoying but necessary
  [[maybe_unused]]
  auto& debugConsole = Akr::Debug::DebugConsole::GetInstance();

  Akr::Core::GetDataLayer<Akr::InputLayer>()->AddController(std::make_shared<Akr::Input::UIInputControler>());

  return 0;
};

std::shared_ptr<Game::Scene> CoreManager::LoadScene(std::shared_ptr<Game::Scene> scene) {
  scene->Load();
  CoreManager::loadedScenes_.push_back(scene);

  return scene;
};

std::shared_ptr<Game::Scene> CoreManager::GetActiveScene() { return CoreManager::activeScene_; }

void CoreManager::SetActiveScene(std::shared_ptr<Game::Scene> scene) {
  if (IsSceneLoaded(GetActiveScene())) {
    UnloadScene(activeScene_);
  }

  // Check if the scene is not already in loadedScenes_
  if (!IsSceneLoaded(scene)) {
    // Load the scene
    if (LoadScene(scene)) {
      // Scene loaded successfully, set it as the active scene
      CoreManager::activeScene_ = scene;
      Core::GetDataLayer<ActiveSceneLayer>()->SetActiveScene(scene);
    } else {
      // Scene loading failed
      spdlog::error("Failed to set active scene: Scene loading failed.");
Debug::DebugConsole::LogError("Failed to set active scene: Scene loading failed.");
    }
  } else {
    // Scene is already loaded, set it as the active scene
    CoreManager::activeScene_ = scene;
  }
}

int CoreManager::UnloadScene(std::shared_ptr<Game::Scene> scene) {
  if (IsSceneLoaded(scene)) {
    if (scene == CoreManager::activeScene_) {
      CoreManager::activeScene_ = nullptr;
    }

    scene->Save();
    scene->Unload();
    CoreManager::loadedScenes_.erase(std::remove(CoreManager::loadedScenes_.begin(), CoreManager::loadedScenes_.end(), scene),
                                     CoreManager::loadedScenes_.end());
    return 0;
  } else {
    return 1;
  }
}

void CoreManager::StartActiveScene() { CoreManager::activeScene_->Start(); };

int CoreManager::Cleanup() { return 0; };

}  // namespace Akr
