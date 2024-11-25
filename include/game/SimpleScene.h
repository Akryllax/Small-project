#pragma once

#include "GObject.h"
#include "GameLayer.h"
#include "IRenderable.h"
#include "ITickable.h"
#include <chrono>
#include <memory>
#include <vector>
namespace Akr::Game {
/**
 * @brief A simple scene class.
 *
 * This class is a simple implementation of the Scene class.
 */
class SimpleScene : public ITickable {
  std::vector<std::shared_ptr<GObject>> sceneObjects;
  std::vector<std::shared_ptr<IRenderable>> renderables;

public:
  SimpleScene() = default;

  void AddObject(std::shared_ptr<GObject> object) {
    sceneObjects.push_back(object);
    if (auto renderable = std::dynamic_pointer_cast<IRenderable>(object)) {
      renderables.push_back(renderable);
    }
  }

  std::shared_ptr<GObject> FindObject(std::string const& name) {
    if (auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(),
                               [&name](std::shared_ptr<GObject> const& object) { return object->GetName() == name; });
        it != sceneObjects.end()) {
      return *it;
    }
    return nullptr;
  }

  bool RemoveObject(std::shared_ptr<GObject> object) {
    if (auto it = std::find(sceneObjects.begin(), sceneObjects.end(), object); it != sceneObjects.end()) {
      sceneObjects.erase(it);
      return true;
    }
    return false;
  }

  void Tick(std::chrono::milliseconds const& delta) final {
    OnTick(delta);
    for (auto const& object : sceneObjects) {
      object->Tick(delta);
    }

    auto renderCommands = std::vector<Renderer::RenderCommand>();
    for (auto const& renderable : renderables) {
      renderable->GenerateRenderCommand();
    }
  }

  virtual void OnTick(std::chrono::milliseconds const& delta) = 0;

  void Load() {
    for (auto const& object : sceneObjects) {
      object->Start();
    }
  }

  void Unload() {
    for (auto const& object : sceneObjects) {
      object->Stop();
    }
  }
};
}  // namespace Akr::Game