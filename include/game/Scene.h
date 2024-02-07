#pragma once

#include "GObject.h"
#include <memory>
#include <string_view>
#include <vector>

namespace Akr::Game {

    class Scene {
    public:
        Scene() : rootGObject_("Root") {
            // Initialize Scene
        }

        // Load a scene from a file or resource
        static void LoadScene(std::string_view const& sceneName) {
            // Implement scene loading logic here
        }

        // Save the current scene to a file or resource
        static void SaveScene(std::string_view const& sceneName) {
            // Implement scene saving logic here
        }

        // Add a GameObject to the root of the scene
        void AddRootObject(std::shared_ptr<GObject> gameObject) {
            rootGObject_.AddChild(gameObject);
        }

        // Remove a GameObject from the scene
        void RemoveRootObject(const std::string& gameObjectName) {
            auto gameObject = rootGObject_.GetChildGObject(gameObjectName);
            if (gameObject) {
                // Remove the gameObject from the root object's children
                // (Assuming AddChild method also appends to GetChildren())
                // Assuming vector-based storage, it might need optimization for large lists.
                rootGObject_.GetChildren().erase(
                    std::remove(rootGObject_.GetChildren().begin(), rootGObject_.GetChildren().end(), gameObject),
                    rootGObject_.GetChildren().end());
            }
        }

        // Get a reference to the root GameObject of the scene
        GObject& GetRootObject() {
            return rootGObject_;
        }

    private:
        Scene(const Scene&) = delete;

        GObject rootGObject_;
    };

}  // namespace Akr::Game