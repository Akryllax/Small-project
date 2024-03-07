#include "DevScene.h"
#include "Button.h"
#include "CoreManager.h"
#include "GObject.h"
#include "InputLayer.h"
#include "Random.h"  // Add missing include statement
#include "TestShip.h"
#include <memory>

namespace Akr::Game {

void DevScene::OnLoad() {
#pragma region initGObjects
  auto testShip1 = GObject::make_shared_gobject<TestShip>("testShip1");
  auto testShip2 = GObject::make_shared_gobject<TestShip>("testShip2");
  auto testShip3 = GObject::make_shared_gobject<TestShip>("testShip3");

  testShip1->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  testShip2->GetBody()->SetTransform(b2Vec2(200, 600), 1);
  testShip3->GetBody()->SetTransform(b2Vec2(400, 300), 0);
#pragma endregion

#pragma region initButtons
  auto resetShipDbgButton = new Akr::UI::Button(0, 400, 200, 40, "Reset ship");
  resetShipDbgButton->SetOnClick([&]() {
    spdlog::trace("Reseting ship position!");
    FindInScene<TestShip>("testShip1")->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  });

  float const impulseMultiplier = 300;

  auto addRandomImpulseShipDbgButton = new Akr::UI::Button(0, 450, 200, 40, "Add random impulse");
  addRandomImpulseShipDbgButton->SetOnClick([&]() {
    // Generate random impulse values in the range of -80 to 80
    float impulseX = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;

    float impulseY = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;

    spdlog::trace("Adding impulse: (dX: {}, dY: {})", impulseX, impulseY);

    // Apply the random impulse to the ship's body
    FindInScene<TestShip>("testShip1")->GetBody()->SetLinearVelocity(b2Vec2(impulseX, impulseY));
  });

  auto loadDevScene1 = new Akr::UI::Button(0, 500, 200, 40, "Load DevScene1");
  loadDevScene1->SetOnClick([&]() {
    auto devScene = std::make_shared<Game::DevScene>();

    Akr::CoreManager::UnloadScene(devScene);
    Akr::CoreManager::SetActiveScene(devScene);
    Akr::CoreManager::StartActiveScene();
  });

#pragma endregion

#pragma region AddToScene
  // Add the test ships to the scene
  AddToScene(testShip1);
  AddToScene(testShip2);
  AddToScene(testShip3);

  // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(resetShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(resetShipDbgButton);

  // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(loadDevScene1);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(loadDevScene1);

  // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(addRandomImpulseShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(addRandomImpulseShipDbgButton);
#pragma endregion
};

void DevScene::OnStart() {
  FindInScene<TestShip>("testShip1")->GetBody()->SetAngularVelocity(std::cos(5 * ALLEGRO_PI / 180.0f));
  FindInScene<TestShip>("testShip1")->GetBody()->SetLinearVelocity(b2Vec2(20, 20));

  FindInScene<TestShip>("testShip2")->GetBody()->SetAngularVelocity(std::cos(5 * ALLEGRO_PI / 180.0f));
  FindInScene<TestShip>("testShip2")->GetBody()->SetLinearVelocity(b2Vec2(-20, 20));

  FindInScene<TestShip>("testShip3")->GetBody()->SetAngularVelocity(std::cos(1 * ALLEGRO_PI / 180.0f));
  FindInScene<TestShip>("testShip3")->GetBody()->SetLinearVelocity(b2Vec2(-20, -20));
};

void DevScene::OnSave(){

};

}  // namespace Akr::Game