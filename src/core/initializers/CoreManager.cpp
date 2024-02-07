#include "CoreManager.h"

#include "Configuration.h"
#include "Core.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "RendererLayer.h"
#include "UIInputController.h"

namespace Akr {
int CoreManager::Initialize() {
  Akr::Configuration::load();
  Akr::Logger::Init();

  Akr::Core::GetInstance().AddDataLayer<Akr::InputLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::NamedLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::LocationLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::RendererLayer>();
  Akr::Core::GetInstance().AddDataLayer<Akr::PhysicsLayer>();

  Akr::Core::GetDataLayer<Akr::InputLayer>()->AddController(std::make_shared<Akr::Input::UIInputControler>());

  return 0;
};

int CoreManager::Cleanup() { return 0; };

}  // namespace Akr
