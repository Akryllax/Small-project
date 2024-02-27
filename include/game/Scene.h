#pragma once

#include "CommonTypes.h"
#include "GObject.h"
#include "Scene.h"
#include "Tree.h"
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Akr::Game {
using GObjTree = Akr::Common::Tree<std::string, std::shared_ptr<Akr::Game::GObject>>;
using GObjTreeNode = Akr::Common::TreeNode<std::string, std::shared_ptr<Akr::Game::GObject>>;

class Scene {
public:
  Scene() {
    // Initialize Scene
    gobjectTree.insert("root", std::make_shared<GObject>("root"));
  }

  explicit Scene(Common::Types::ByteVector const& inputString)
      : Akr::Game::Scene(){
            // Load from serialized bytestring
        };

  void Load() { OnLoad(); };

  void Save() { OnSave(); };

  void Start() { OnStart(); };

  virtual void OnLoad(){};
  virtual void OnSave(){};
  virtual void OnStart(){};

  Common::Types::ByteVector const Serialize() {
    Common::Types::ByteVector output;

    return output;
  };

  // Remove a GameObject from the scene
  void RemoveRootObject(std::string const& gameObjectName) {
    auto gameObject = gobjectTree.find(gameObjectName);
    if (gameObject) {
      gobjectTree.remove(gameObjectName);
    }
  }

  void AddToScene(std::shared_ptr<GObject> gObject) {
    // Check if the object is not already in the scene
    if (!FindInScene(gObject->GetName())) {
      // Add the object to the scene
      gobjectTree.insert(gObject->GetName(), gObject);
    }
  }

  std::shared_ptr<GObject> FindInScene(std::string name) {
    // Find the object in the scene by its name
    auto foundGObj = gobjectTree.find(name);
    return (foundGObj) ? gobjectTree.find(name)->getData() : nullptr;
  }

  void DeleteGObject(std::shared_ptr<GObject> gameObject) {
    // Remove the object from the scene
    gobjectTree.remove(gameObject->GetName());
  }

  // Get a reference to the root GameObject of the scene
  GObject& GetRootObject() { return *gobjectTree.find("root")->getData(); }

  std::shared_ptr<GObjTreeNode> GetTreeRoot() { return gobjectTree.root(); }

  // Add a GameObject to the root of the scene
  void AddRootObject(std::shared_ptr<GObject> gameObject) { gobjectTree.insert(gameObject->GetName(), gameObject); }

#pragma region STATIC METHODS
  // Load a scene from a file or resource
  static void LoadScene(std::string_view const& sceneName) {
    // Implement scene loading logic here
  }

  // Save the current scene to a file or resource
  static void SaveScene(std::string_view const& sceneName) {
    // Implement scene saving logic here
  }
#pragma endregion

private:
  Scene(Scene const&) = delete;

  GObjTree gobjectTree;
};

}  // namespace Akr::Game
