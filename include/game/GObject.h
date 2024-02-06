#include "Core.h"
#include "PhysicsLayer.h"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include "spdlog.h"
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Akr::Game {

class GObject : private std::enable_shared_from_this<GObject> {
public:
  GObject() {
    // Define the body here and attach it to the world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    body_ = Akr::Core::GetDataLayer<PhysicsLayer>()->GetBox2DWorld().CreateBody(&bodyDef);
  };

  GObject(std::string const& name) : name_(name){};

  virtual ~GObject() = default;

  b2Transform const& GetTransform() {
    if (!body_) {
      spdlog::error("Trying to get transform of an GObject without a body!");
      static b2Transform nullTransform;
      return nullTransform;
    }
    return body_->GetTransform();
  };

  void setName(std::string_view const& newName) { name_ = newName; }

  std::string GetName() const { return name_; }

  // Add a child object to the current object
  void AddChild(std::shared_ptr<GObject> newChild) {
    newChild->parent_ = shared_from_this();  // Set the parent of the child
    children_.push_back(newChild);
  };

  // Get a child object by its name
  std::shared_ptr<GObject> GetChildGObject(std::string_view const& name) {
    for (auto const& child : children_) {
      if (child->GetName() == name) {
        return child;
      }
    }
    return nullptr;  // Return nullptr if no child with the given name is found
  };

  std::vector<std::shared_ptr<GObject>>& GetChildren()
  {
    return children_;
  }

private:
  std::string name_;

  std::shared_ptr<GObject> parent_;
  std::vector<std::shared_ptr<GObject>> children_;

  b2Body* body_;
  b2BodyDef bodyDef_;

  //Protect from accidental copy
  GObject(const GObject&) = delete;
};

}  // namespace Akr::Game
