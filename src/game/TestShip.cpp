#include "TestShip.h"
#include "DebugConsole.h"

#include "CompositeRenderCommand.h"
#include "DrawBitmapOperation.h"
#include "RendererLayer.h"
#include "PhysicsLayer.h"
#include "RendererLayer.h"
#include "Core.h"
#include "Rect.h"

namespace Akr {

TestShip::TestShip(std::string const& name) : Game::GObject(name), RigidBody(name, &(Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld())) {
  starshipDef.type = b2_dynamicBody;
  SetBitmapResource(std::make_shared<BitmapResource>("1.png"));
  GetBitmapResource()->load();
  assert(body);
  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderablePtr(this);
}

void TestShip::render() {
  // Deprecated render function implementation
}

std::shared_ptr<Renderer::RenderCommand> TestShip::GenerateRenderCommand() {
  auto compositeCommand = std::make_shared<Akr::Renderer::CompositeRenderComand>();

  Math::Rect rect{this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y, this->GetBody()->GetPosition().x,
                  this->GetBody()->GetPosition().y, this->GetBody()->GetAngle()};

  compositeCommand->QueueCommand(std::make_shared<Renderer::DrawBitmapOperation>(GetBitmapResource()->getBitmap(), rect));

  #ifdef DEBUG
  Debug::DebugConsole::Log("Rendered ship: " + GetName());

  #endif

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer().DrawArrowDebug(
      this->GetBody()->GetPosition(), this->GetBody()->GetPosition() + this->GetBody()->GetLinearVelocity());

  return compositeCommand;
}

void TestShip::TakeControl() {
  // Implementation of TakeControl method
}

void TestShip::ReleaseControl() {
  // Implementation of ReleaseControl method
}

void TestShip::OnEvent() {
  // Implementation of OnEvent method
}

void TestShip::OnRawInput(std::chrono::milliseconds const& delta) {
  // Implementation of OnRawInput method
}

void TestShip::OnSelect() {
  Debug::DebugConsole::Log("Selected ship: " + GetName());
  // Implementation of OnSelect method
}

void TestShip::OnDeselect() {
  Debug::DebugConsole::Log("Selected ship: " + GetName());
  // Implementation of OnOnDeselect method
}
}  // namespace Akr
