#pragma once

#include "Entity.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include <cassert>

namespace Akr {
class RigidBody : public Entity {
public:
  RigidBody(std::string const& name, b2World* world) : Entity(name) {
    // Define the body here and attach it to the world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
  }

private:
  RigidBody& operator=(RigidBody const&) = delete;
  RigidBody(RigidBody const&) = delete;

protected:
  b2Body* body;

public:
  b2Body* GetBody() {
    assert(body);
    return this->body;
  }
};

}; // namespace Akr