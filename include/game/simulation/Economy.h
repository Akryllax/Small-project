#pragma once

#include "ITickable.h"
#include <spdlog/spdlog.h>

namespace Akr::Game::Simulation {

/**
 * @brief The Economy class represents the economy simulation in the game.
 *
 * It is responsible for managing the game's economy and performing economic calculations.
 * The Economy class is a singleton class that can be accessed using the GetInstance() method.
 * It implements the ITickable interface, allowing it to be updated on each game tick.
 */
class Economy : public ITickable {
public:
  /**
   * @brief Get the instance of the Economy class.
   *
   * @return Economy& The reference to the Economy instance.
   */
  static Economy& GetInstance() {
    static Economy instance;
    return instance;
  }

  /**
   * @brief Initialize the Economy.
   *
   * This method is called when the game starts to initialize the Economy.
   */
  void Initialize() { spdlog::info("Initializing Economy..."); }

  /**
   * @brief Update the Economy on each game tick.
   *
   * @param delta The time elapsed since the last tick.
   */
  void Tick(std::chrono::milliseconds const& delta) { spdlog::trace("Economy ticking..."); }

  /**
   * @brief Kill the Economy.
   *
   * This method is called when the game is shutting down to clean up the Economy.
   */
  void Kill() { spdlog::info("Killing Economy..."); }

  /**
   * @brief Save the state of the Economy.
   *
   * This method is called when the game is saving its state to persist the Economy's data.
   */
  void OnSave() { spdlog::info("Saving Economy..."); }

  /**
   * @brief Unload the Economy.
   *
   * This method is called when the game is unloading to release any resources held by the Economy.
   */
  void OnUnload() { spdlog::info("Unloading Economy..."); }

  ~Economy() = default;

private:
  Economy() = default;
  Economy(Economy const&) = delete;
  Economy& operator=(Economy const&) = delete;
};

};  // namespace Akr::Game::Simulation