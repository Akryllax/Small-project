#pragma once

#include "CommonTypes.h"
#include "GObject.h"
#include "Tree.h"
#include "spdlog/spdlog.h"
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

/**
 * @brief The Scene class represents a scene in a game.
 *
 * A scene is a container that holds game objects and provides
 * functionality for loading, unloading, saving, and starting the scene.
 * It also allows adding, removing, and finding game objects within the scene.
 */
namespace Akr::Game {
using GObjTree = Akr::Common::Tree<std::string, std::shared_ptr<Akr::Game::GObject>>;
using GObjTreeNode = Akr::Common::TreeNode<std::string, std::shared_ptr<Akr::Game::GObject>>;

class Scene {
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the scene by inserting a root game object.
   */
  Scene() {
    // Initialize Scene
    gobjectTree.insert("root", std::make_shared<GObject>("root"));
  }

  /**
   * @brief Destructor.
   */
  virtual ~Scene() = default;

  /**
   * @brief Constructor that takes a serialized byte vector as input.
   *
   * @param inputString The serialized byte vector representing the scene.
   */
  explicit Scene(Common::Types::ByteVector const& inputString)
      : Akr::Game::Scene(){
            // Load from serialized bytestring
        };

  /**
   * @brief Load the scene.
   *
   * Calls the virtual OnLoad() function.
   */
  void Load() { OnLoad(); };

  /**
   * @brief Unload the scene.
   *
   * Calls the virtual OnUnload() function.
   */
  void Unload() { OnUnload(); };

  /**
   * @brief Save the scene.
   *
   * Calls the virtual OnSave() function.
   */
  void Save() { OnSave(); };

  /**
   * @brief Start the scene.
   *
   * Calls the virtual OnStart() function.
   */
  void Start() { OnStart(); };

  /**
   * @brief Virtual function called when the scene is loaded.
   *
   * This function can be overridden in derived classes to perform
   * additional operations when the scene is loaded.
   */
  virtual void OnLoad(){};

  /**
   * @brief Virtual function called when the scene is unloaded.
   *
   * This function can be overridden in derived classes to perform
   * additional operations when the scene is unloaded.
   */
  virtual void OnUnload(){};

  /**
   * @brief Virtual function called when the scene is saved.
   *
   * This function can be overridden in derived classes to perform
   * additional operations when the scene is saved.
   */
  virtual void OnSave(){};

  /**
   * @brief Virtual function called when the scene is started.
   *
   * This function can be overridden in derived classes to perform
   * additional operations when the scene is started.
   */
  virtual void OnStart(){};

  /**
   * @brief Serialize the scene to a byte vector.
   *
   * @return The serialized byte vector representing the scene.
   */
  Common::Types::ByteVector Serialize() const {
    Common::Types::ByteVector output;

    return output;
  };

  /**
   * @brief Remove a game object from the scene.
   *
   * @param gameObjectName The name of the game object to remove.
   */
  void RemoveRootObject(std::string const& gameObjectName) {
    auto gameObject = gobjectTree.find(gameObjectName);
    if (gameObject) {
      gobjectTree.remove(gameObjectName);
    }
  }

  /**
   * @brief Add a game object to the scene.
   *
   * @param gObject The game object to add.
   */
  void AddToScene(std::shared_ptr<GObject> gObject) {
    // Check if the object is not already in the scene
    if (!FindInScene(gObject->GetName())) {
      // Add the object to the scene
      gobjectTree.insert(gObject->GetName(), gObject);
    }
  }

  /**
   * @brief Find a game object in the scene by its name.
   *
   * @tparam T The type of game object to find.
   * @param name The name of the game object to find.
   * @return A shared pointer to the found game object, or an empty shared pointer if not found.
   */
  IS_CHILD_OF_TYPE_T_DEFAULTS(GObject)
  std::shared_ptr<T> FindInScene(std::string name) {
    // Find the object in the scene by its name
    auto foundGObj = gobjectTree.find(name);
    if (foundGObj) {
      return std::dynamic_pointer_cast<T>(foundGObj->getData());
    } else {
      spdlog::error("[Scene] Game object not found in scene: {}", name);
      return nullptr;
    }
  }

  /**
   * @brief Delete a game object from the scene.
   *
   * @param gameObject The game object to delete.
   */
  void DeleteGObject(std::shared_ptr<GObject> gameObject) {
    // Remove the object from the scene
    gobjectTree.remove(gameObject->GetName());
  }

  /**
   * @brief Get a reference to the root game object of the scene.
   *
   * @return A reference to the root game object.
   */
  GObject& GetRootObject() { return *gobjectTree.find("root")->getData(); }

  /**
   * @brief Get a shared pointer to the root node of the game object tree.
   *
   * @return A shared pointer to the root node of the game object tree.
   */
  std::shared_ptr<GObjTreeNode> GetTreeRoot() { return gobjectTree.root(); }

  /**
   * @brief Add a game object to the root of the scene.
   *
   * @param gameObject The game object to add.
   */
  void AddRootObject(std::shared_ptr<GObject> gameObject) { gobjectTree.insert(gameObject->GetName(), gameObject); }

#pragma region STATIC METHODS
  /**
   * @brief Load a scene from a file or resource.
   *
   * @param sceneName The name of the scene to load.
   */
  static void LoadScene(std::string_view const& sceneName) {
    // Implement scene loading logic here
  }

  /**
   * @brief Save the current scene to a file or resource.
   *
   * @param sceneName The name of the scene to save.
   */
  static void SaveScene(std::string_view const& sceneName) {
    // Implement scene saving logic here
  }
#pragma endregion

private:
  Scene(Scene const&) = delete;

  GObjTree gobjectTree;
};

}  // namespace Akr::Game
