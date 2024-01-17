#include "Core.h"
#include "DataLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "box2d/b2_body.h"
#include "box2d/box2d.h"
#include <gtest/gtest.h>
#include <memory>
#include "Logger.h"

class Box2DIntegration : public ::testing::Test {
protected:
    void SetUp() override {
        // Remove existing config file before each test
        Akr::Logger::init("Box2DIntegration.log");
    }

    void TearDown() override {
    }

    Box2DIntegration() = default;
};

TEST(Box2DIntegration, BasicTest) {
  auto& core1 = Akr::Core::GetInstance();
  auto& core2 = Akr::Core::GetInstance();

  ASSERT_EQ(&core1, &core2);
}

TEST(Box2DIntegration, WorldCreation_Bare_Ok) {
  Akr::World world;

  // Create a Box2D body definition
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);

  // Set the body definition properties as needed
  // ...

  // Create a Box2D body using the world's Box2D world
  auto body = world.GetBox2DWorld().CreateBody(&bodyDef);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  body->CreateFixture(&fixtureDef);

  // Set the body properties as needed
  // ...

  // Assuming you have a b2Body named 'body'
  b2Vec2 newPosition(5.0f, 3.0f);  // Set the new position coordinates
  float newAngle = 0.0f;           // Set the new angle (in radians)

  body->SetTransform(newPosition, newAngle);

  auto pos1 = body->GetPosition();

  spdlog::trace("Before applying force - pos1: ({}, {})", pos1.x, pos1.y);

  body->ApplyForce(b2Vec2(0, 20), b2Vec2(0, 0), true);
  ASSERT_NE(body, nullptr);

  for (int32 i = 0; i < 60; ++i) {
    world.GetBox2DWorld().Step(1 / 60.0, 6, 2);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  auto pos2 = body->GetPosition();

  spdlog::trace( "After applying force - pos2: ({}, {})", pos2.x, pos2.y);

  ASSERT_NE(pos1, pos2);
}

// TEST(Box2DIntegration, WorldMinimuExample) {
//   b2Vec2 gravity(0.0f, -10.0f);

//   b2World world(gravity);

//   b2BodyDef groundBodyDef;
//   groundBodyDef.position.Set(0.0f, -10.0f);

//   b2Body* groundBody = world.CreateBody(&groundBodyDef);

//   b2PolygonShape groundBox;
//   groundBox.SetAsBox(50.0f, 10.0f);

//   groundBody->CreateFixture(&groundBox, 0.0f);

//   b2BodyDef bodyDef;
//   bodyDef.type = b2_dynamicBody;
//   bodyDef.position.Set(0.0f, 4.0f);
//   b2Body* body = world.CreateBody(&bodyDef);

//   b2PolygonShape dynamicBox;
//   dynamicBox.SetAsBox(1.0f, 1.0f);

//   b2FixtureDef fixtureDef;
//   fixtureDef.shape = &dynamicBox;
//   fixtureDef.density = 1.0f;
//   fixtureDef.friction = 0.3f;

//   body->CreateFixture(&fixtureDef);

//   float timeStep = 1.0f / 60.0f;

//   int32 velocityIterations = 6;
//   int32 positionIterations = 2;

//   for (int32 i = 0; i < 60; ++i) {
//     world.Step(timeStep, velocityIterations, positionIterations);
//     b2Vec2 position = body->GetPosition();
//     float angle = body->GetAngle();
//     printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//   }
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
