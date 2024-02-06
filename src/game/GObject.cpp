#include "GObject.h"

namespace Akr::Game {

GObject::GObject() {
  // Define the body here and attach it to the world
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  body_ = Akr::Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld().CreateBody(&bodyDef);
}

GObject::GObject(std::string const& name) : name_(name) {}

b2Transform const& GObject::GetTransform() const {
  if (!body_) {
    spdlog::error("Trying to get transform of an GObject without a body!");
    static b2Transform nullTransform;
    return nullTransform;
  }
  return body_->GetTransform();
}

void GObject::setName(std::string_view const& newName) { name_ = newName; }

std::string GObject::GetName() const { return name_; }

void GObject::AddChild(std::shared_ptr<GObject> newChild) {
  newChild->parent_ = shared_from_this();  // Set the parent of the child
  children_.push_back(newChild);
}

std::shared_ptr<GObject> GObject::GetChildGObject(std::string_view const& name) {
  for (auto const& child : children_) {
    if (child->GetName() == name) {
      return child;
    }
  }
  return nullptr;  // Return nullptr if no child with the given name is found
}

std::vector<std::shared_ptr<GObject>>& GObject::GetChildren() { return children_; }

}  // namespace Akr::Game
