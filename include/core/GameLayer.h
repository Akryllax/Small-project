#pragma once

#include "Core.h"
#include "DataLayer.h"
#include "Dev.h"
#include "GObject.h"
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


  /**
   * @brief Updates the game state based on the elapsed time.
   *
   * This function is called to update the game state based on the elapsed time since the last update.
   *
   * @param delta The elapsed time since the last update.
   */
  void Tick(std::chrono::milliseconds const& delta) override{};
  void Kill() override{};
  size_t GetExecPriority() const override { return EXEC_PRIORITY; }

  /**
   * @brief Tracks a GObject
   * @param sharedGObj_: shared pointer to the GObject to track
   * The GObject is added to the trackedGObjects_ vector.
   */
  IS_CHILD_OF_TYPE_T(Game::GObject)
  void TrackGObject(std::shared_ptr<T> sharedGObj_) { trackedGObjects_.push_back(sharedGObj_); }

  /**
   * @brief Check if a GObject is tracked
   * @param sharedGObj: shared pointer to the GObject to check
   * @return true if the GObject is tracked, false otherwise
   * Iterates through the trackedGObjects_ vector and checks if the shared pointer points to the same object as the tracked object.
   */
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

  /*
   * Untrack a GObject
   * @param sharedGObj: shared pointer to the GObject to untrack
   * If the GObject is found in the trackedGObjects_ vector, it is removed. Safe to call even if the GObject is not tracked.
   */
  IS_CHILD_OF_TYPE_T(Game::GObject)
  void UntrackGObject(std::shared_ptr<T> sharedGObj) {
    // Find the shared pointer in the vector and remove it
    trackedGObjects_.erase(std::remove(trackedGObjects_.begin(), trackedGObjects_.end(), sharedGObj), trackedGObjects_.end());
  }

private:
  GameLayer& operator=(GameLayer const&) = delete;
  GameLayer(GameLayer const&) = delete;

  // Vector to store the tracked GObjects
  std::vector<std::shared_ptr<Game::GObject>> trackedGObjects_;
};
}  // namespace Akr
