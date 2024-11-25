#include "DebugConsole.h"
#include "SimpleScene.h"
#include "TestShip.h"
#include <chrono>

namespace Akr::Game {

class SimpleDevScene : public SimpleScene {
public:
  std::array<std::shared_ptr<TestShip>, 10> ships;

  void Start() override {
    ships[0] = GObject::make_shared_gobject<TestShip>("TestShip1");
    ships[1] = GObject::make_shared_gobject<TestShip>("TestShip2");
    ships[2] = GObject::make_shared_gobject<TestShip>("TestShip3");

    AddObject(ships[0]);
    AddObject(ships[1]);
    AddObject(ships[2]);

    ships[0]->GetBody()->SetTransform(b2Vec2(200, 200), 0);
    ships[1]->GetBody()->SetTransform(b2Vec2(200, 600), 1);
    ships[2]->GetBody()->SetTransform(b2Vec2(400, 300), 0);
  };

  void OnTick(std::chrono::milliseconds const& delta) override {
    Debug::DebugConsole::Log("SimpleDevScene::OnTick()");
  };
};
}  // namespace Akr::Game