#pragma once

#include "CommonTypes.h"
#include "GObject.h"
#include "Scene.h"
#include "Tree.h"
#include <memory>
#include <string_view>
#include <vector>

namespace Akr::Game {

class Scene {
public:
    Scene() {
        // Initialize Scene
        gobjectTree.insert("root", std::make_shared<GObject>("root"));
    }

    explicit Scene(const Common::Types::ByteVector& inputString) : Akr::Game::Scene() {
        // Load from serialized bytestring
    };

    void Load() {
        OnLoad();
    };

    void Save() {
        OnSave();
    };

    virtual void OnLoad() {};
    virtual void OnSave() {};

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

    // Get a reference to the root GameObject of the scene
    GObject& GetRootObject() { return *gobjectTree.find("root")->getData(); }

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

    Akr::Common::Tree<std::string_view, std::shared_ptr<GObject>> gobjectTree;
};

} // namespace Akr::Game
