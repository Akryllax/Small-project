#pragma once

#include "Entity.h"
#include "box2d/b2_body.h"
#include <cassert>
#include <memory>
namespace Akr {
class RigidBody : public Entity {
 public:
  RigidBody(b2Body* body, std::string const& name) : Entity(name){};

 protected:
  b2Body* body;

 public:
  void attachBody(b2Body* targetBody) { this->body = targetBody; }
  b2Body* GetBody() {
    assert(body);
    return this->body;
  };
};
}  // namespace Akr