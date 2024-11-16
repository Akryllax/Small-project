#include "TestShip.h"
#include "CompositeRenderCommand.h"
#include "Core.h"
#include "DebugConsole.h"
#include "DebugRenderer.h"
#include "DrawBitmapOperation.h"
#include "ISelectable.h"
#include "PhysicsLayer.h"
#include "Rect.h"
#include "RendererLayer.h"
#include <allegro5/color.h>
#include <wingdi.h>

namespace Akr {

TestShip::TestShip(std::string const& name) : Game::GObject(name), RigidBody(name, &(Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld())) {
  starshipDef.type = b2_dynamicBody;
  SetBitmapResource(std::make_shared<BitmapResource>("1.png"));
  GetBitmapResource()->load();
  uiBoundingRect_ = Math::Rect{-75, -75, 150, 150};
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

  Akr::Renderer::DebugRenderer::DrawBoundingBoxStatic(
      this->uiBoundingRect_ + this->GetBody()->GetPosition(),
      (Akr::Game::ISelectable::GetSelected() == this) ? al_map_rgb(255, 255, 255) : al_map_rgb(125, 125, 125));  // Draw bounding box
  Akr::Renderer::DebugRenderer::DrawArrowStatic(this->GetBody()->GetPosition(),
                                                this->GetBody()->GetPosition() + this->GetBody()->GetLinearVelocity());

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
}  // namespace Akr
