#pragma once

#include "Entity.h"
#include "box2d/b2_body.h"
#include <cassert>
#include <memory>
namespace Akr {
class RigidBody : public Entity {
 public:
  RigidBody(std::string const& name) : Entity(name){};

 protected:
  b2Body* body;

  void attachBody(b2Body* targetBody) { this->body = targetBody; }

 public:
  b2Body* GetBody() {
    assert(body);
    return this->body;
  };
};
}  // namespace Akr