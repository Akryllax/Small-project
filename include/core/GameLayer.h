#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "Dev.h"
#include "GObject.h"
#include "IsDerivedFrom.h"
#include "gtest/gtest.h"
#include <memory>
#include <system_error>
#include <type_traits>

namespace Akr {
namespace Game {
class GObject;
};

class GameLayer : public DataLayer {
public:
  constexpr static size_t EXEC_PRIORITY = 100;
  GameLayer() = default;
  ~GameLayer() override = default;

  void Initialize() override{};

  void Tick(std::chrono::milliseconds const& delta) override{};
  void Kill() override{};
  size_t GetExecPriority() const override { return EXEC_PRIORITY; }

  IS_CHILD_OF_TYPE_T(Game::GObject)
  void TrackGObject(std::shared_ptr<T> sharedGObj_) { trackedGObjects_.push_back(sharedGObj_); }

  IS_CHILD_OF_TYPE_T(Game::GObject)
  bool IsGObjectTracked(std::shared_ptr<T> sharedGObj) {
    // Iterate through the tracked objects vector
    for (auto const& trackedObj : trackedGObjects_) {
      // Check if the shared pointer points to the same object as the tracked object
      if (sharedGObj == trackedObj) {
        return true;  // Object is tracked
      }
    }
    return false;  // Object is not tracked
  }

  IS_CHILD_OF_TYPE_T(Game::GObject)
  void UntrackGObject(std::shared_ptr<T> sharedGObj) {
    // Find the shared pointer in the vector and remove it
    trackedGObjects_.erase(std::remove(trackedGObjects_.begin(), trackedGObjects_.end(), sharedGObj), trackedGObjects_.end());
  }

private:
  GameLayer& operator=(GameLayer const&) = delete;
  GameLayer(GameLayer const&) = delete;

  std::vector<std::shared_ptr<Game::GObject>> trackedGObjects_;
};
}  // namespace Akr
