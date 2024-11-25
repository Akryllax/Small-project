#pragma once

#include "CoreManager.h"
#include "Dev.h"
#include "Scene.h"
#include "SimpleScene.h"
#include <memory>

namespace Akr {

/**
 * @brief The CoreManager class manages initialization and cleanup tasks related to the core functionality of the
 * application.
 */
class CoreManager {
public:
  /**
   * @brief Initializes the core functionality of the application.
   * @return Returns 0 on success, or an error code otherwise.
   */
  static int Initialize();

  /**
   * @brief Cleans up and deallocates resources used by the core functionality of the application.
   * @return Returns 0 on success, or an error code otherwise.
   */
  static int Cleanup();

  /**
   * @brief Loads a scene into the application.
   */
  static int LoadScene(std::string sceneName) { throw NotImplementedException(); };

  /**
   * @brief Loads a scene into the application.
   */
  static std::shared_ptr<Game::Scene> LoadScene(std::shared_ptr<Game::Scene> scene);

  /**
   * @brief Unloads the currently active scene.
   */
  static int UnloadScene(std::shared_ptr<Game::Scene> scene);

  /**
   * @brief Saves the currently active scene.
   */
  static bool SaveScene(std::shared_ptr<Game::Scene> scene) { throw NotImplementedException(); };

  /**
   * @brief Gets the active scene.
   * @return A shared pointer to the active scene.
   */
  static std::shared_ptr<Game::Scene> GetActiveScene();

  static int GetActiveSceneIndex() { throw NotImplementedException(); };

  static void SetActiveScene(int index) { throw NotImplementedException(); };

  static void SetActiveScene(std::shared_ptr<Game::Scene> scene);

  static void SetSimpleActiveScene(std::shared_ptr<Akr::Game::SimpleScene> scene);

  static void StartActiveScene();

  static bool IsASceneActive() { return activeScene_ != nullptr; }

  /**
   * @brief Checks if a scene is already loaded.
   * @param sceneName The name of the scene to check.
   * @return True if the scene is already loaded, false otherwise.
   */
  static bool IsSceneLoaded(std::shared_ptr<Game::Scene> scene) {
    for (auto const& itScene : loadedScenes_) {
      if (itScene == scene) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Gets the name of the active scene.
   * @return The name of the active scene.
   */
  static std::string const GetActiveSceneName();

private:
  inline static std::shared_ptr<Akr::Game::Scene> activeScene_;               /**< The currently active scene. */
  inline static std::vector<std::shared_ptr<Akr::Game::Scene>> loadedScenes_; /**< The currently active scene. */
  inline static std::shared_ptr<Akr::Game::SimpleScene> simpleActiveScene_;
};

}  // namespace Akr
