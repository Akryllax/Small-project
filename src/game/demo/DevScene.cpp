#include "DevScene.h"
#include "GObject.h"
#include "TestShip.h"
#include <memory>
namespace Akr::Game {

void DevScene::OnLoad(){
  auto testShip1 = GObject::make_shared_gobject<TestShip>("testShip");
  auto testShip2 = GObject::make_shared_gobject<TestShip>("testShip");
  auto testShip3 = GObject::make_shared_gobject<TestShip>("testShip");

  AddToScene(testShip1);
  AddToScene(testShip2);
  AddToScene(testShip3);

};
void DevScene::OnSave(){

};

}  // namespace Akr::Game