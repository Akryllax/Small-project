#pragma once

// C++ system headers
#include <cassert>
#include <chrono>
#include <memory>

// Other libraries' .h files
#include "box2d/b2_body.h"
#include <allegro5/allegro.h>

// Your project's .h files
#include "GObject.h"
#include "IControllable.h"
#include "IRenderable.h"
#include "ISelectable.h"
#include "RenderCommand.h"
#include "RigidBody.h"


namespace Akr {

/**
 * @brief The TestShip class represents a test ship entity in the game.
 */
class TestShip : public Game::GObject, public RigidBody, public IRenderable, public IControllable, public Game::ISelectable {
public:
  /**
   * @brief Constructs a new TestShip object with the specified name.
   * @param name The name of the test ship.
   */
  TestShip(std::string const& name);

  /**
   * @brief Default destructor for the TestShip class.
   */
  ~TestShip() override = default;

  // Deprecated render function
  [[deprecated("Use the RenderCommands mode, this is for debugging")]] void render() override;

  /**
   * @brief Generates a render command for rendering the test ship.
   * @return A shared pointer to the generated render command.
   */
  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override;

  // Controllable interface methods
  void TakeControl() override;
  void ReleaseControl() override;
  void OnEvent() override;
  void OnRawInput(std::chrono::milliseconds const& delta) override;
  bool OnSelect() override {
    // Implementation of OnSelect method
    return true;
  }
  bool OnDeselect() override {
    // Implementation of OnOnDeselect method
    return true;
  }

private:
  TestShip(TestShip const&) = delete;             // Deleted copy constructor
  TestShip& operator=(TestShip const&) = delete;  // Deleted copy assignment operator

  b2BodyDef starshipDef;
};

}  // namespace Akr
