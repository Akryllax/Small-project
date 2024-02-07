#include "TestShip.h"

namespace Akr {

TestShip::TestShip(std::string const& name) : RigidBody(name, &(Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld())) {
  starshipDef.type = b2_dynamicBody;
  setBitmapResource(std::make_shared<BitmapResource>("1.png"));
  GetBitmapResource()->load();
  assert(body);
}

void TestShip::render() {
  // Deprecated render function implementation
}

std::shared_ptr<Renderer::RenderCommand> TestShip::GenerateRenderCommand() {
  auto compositeCommand = std::make_shared<Akr::Renderer::CompositeRenderComand>();

  Math::Rect rect{this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y,
                  this->GetBody()->GetPosition().x, this->GetBody()->GetPosition().y, this->GetBody()->GetAngle()};

  compositeCommand->QueueCommand(
      std::make_shared<Renderer::DrawBitmapOperation>(GetBitmapResource()->getBitmap(), rect));

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer().DrawArrow(
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

} // namespace Akr
