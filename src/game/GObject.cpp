#include "GObject.h"
#include "INamedObject.h"
#include "PhysicsLayer.h"
#include "DebugConsole.h"

namespace Akr::Game {

GObject::GObject() : Akr::Common::INamedObject("UnnamedObject") {
  // Define the body here and attach it to the world
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  body_ = Akr::Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld().CreateBody(&bodyDef);
}

b2Transform const& GObject::GetTransform() const {
  if (!body_) {
    spdlog::error("Trying to get transform of an GObject without a body!");
    Debug::DebugConsole::LogError("Trying to get transform of an GObject without a body!");
    static b2Transform nullTransform;
    return nullTransform;
  }
  return body_->GetTransform();
}
}  // namespace Akr::Game
