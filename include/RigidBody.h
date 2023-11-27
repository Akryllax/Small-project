#include "Entity.h"
#include "box2d/b2_body.h"
#include <memory>
namespace Akr {
class RigidBody : public Entity {
 public:
  RigidBody(std::shared_ptr<b2Body> body, std::string const& name)
      : Entity(name), body(body){};

 protected:
  std::shared_ptr<b2Body> body;

 public:
  void attachBody(std::shared_ptr<b2Body> targetBody) {
    this->body = targetBody;
  }
};
}  // namespace Akr