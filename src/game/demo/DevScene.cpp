#include "DevScene.h"
#include "Button.h"
#include "CoreManager.h"
#include "DataLayer.h"
#include "GObject.h"
#include "GameLayer.h"
#include "InputLayer.h"
#include "Random.h"  // Add missing include statement
#include "TestShip.h"
#include "UIRectangle.h"
#include "allegro5/color.h"
#include <memory>

namespace Akr::Game {

void DevScene::OnStart() {
  ships[0]->GetBody()->SetAngularVelocity(std::cos(5 * ALLEGRO_PI / 180.0f));
  ships[0]->GetBody()->SetLinearVelocity(b2Vec2(20, 20));

  ships[1]->GetBody()->SetAngularVelocity(std::cos(5 * ALLEGRO_PI / 180.0f));
  ships[1]->GetBody()->SetLinearVelocity(b2Vec2(-20, 20));

  ships[2]->GetBody()->SetAngularVelocity(std::cos(1 * ALLEGRO_PI / 180.0f));
  ships[2]->GetBody()->SetLinearVelocity(b2Vec2(-20, -20));
};

void DevScene::OnLoad() {
  /// GAME OBJECTS

  ships[0] = GObject::make_shared_gobject<TestShip>("testShip1");
  ships[1] = GObject::make_shared_gobject<TestShip>("testShip2");
  ships[2] = GObject::make_shared_gobject<TestShip>("testShip3");

  ships[0]->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  ships[1]->GetBody()->SetTransform(b2Vec2(200, 600), 1);
  ships[2]->GetBody()->SetTransform(b2Vec2(400, 300), 0);

  /// UI ELEMENTS

  auto resetShipDbgButton = new Akr::UI::Button(0, 400, 200, 40, "Reset ship");
  resetShipDbgButton->SetOnClick([&]() {
    spdlog::trace("Reseting ship position!");
    ships[0]->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  });

  float const impulseMultiplier = 300;

  auto addRandomImpulseShipDbgButton = new Akr::UI::Button(0, 450, 200, 40, "Add random impulse");
  addRandomImpulseShipDbgButton->SetOnClick([&]() {
    // Generate random impulse values in the range of -80 to 80
    float impulseX = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;

    float impulseY = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;

    spdlog::trace("Adding impulse: (dX: {}, dY: {})", impulseX, impulseY);

    // Apply the random impulse to the ship's body
    ships[0]->GetBody()->SetLinearVelocity(b2Vec2(impulseX, impulseY));
  });

  auto uiRect = new Akr::UI::UIRectangle(0, 0, 100, 100, al_map_rgb(255, 0, 0), 1.0f);

  /// ADD TO SCENE

  // Add the test ships to the scene
  AddToScene(ships[0]);
  AddToScene(ships[1]);
  AddToScene(ships[2]);

  // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(resetShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(resetShipDbgButton);

  // // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(loadDevScene1);
  // Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(loadDevScene1);

  // Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(addRandomImpulseShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(addRandomImpulseShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListenerPtr(uiRect);
};

void DevScene::OnSave(){

};

void DevScene::OnUnload() {
  // Unload the test ships from the scene
  Akr::Core::GetDataLayer<Akr::InputLayer>()->ClearAllInputs();
  Akr::Core::GetDataLayer<Akr::GameLayer>()->UntrackGObject(ships[0]);
};

void DevScene::Tick(std::chrono::milliseconds const& delta) {
  auto& coreRenderer = Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer();

  auto frameCount = Akr::Core::GetFrameCount();

  coreRenderer.DrawCross(b2Vec2(200.f + 20 * static_cast<float>(frameCount) * 1.f/60.f, 400.f), al_map_rgb(255, 255, 255));
};

}  // namespace Akr::Game