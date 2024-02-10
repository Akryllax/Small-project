#include "DevScene.h"
#include "TestShip.h"
#include <memory>
namespace Akr::Game {

void DevScene::OnLoad(){
  auto testShip = std::make_shared<TestShip>("");

  auto sceneRoot = this->GetTreeRoot();

};
void DevScene::OnSave(){

};

}  // namespace Akr::Game