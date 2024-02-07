#pragma once

#include "Configuration.h"
#include "Core.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "RendererLayer.h"
#include "UIInputController.h"

namespace Akr::Init {
class CoreManager {
public:
  static int Initialize(Akr::Core& coreInstance) {
    Akr::Configuration::load();
    Akr::Logger::init("core.log");

    coreInstance.AddDataLayer<Akr::InputLayer>();
    coreInstance.AddDataLayer<Akr::NamedLayer>();
    coreInstance.AddDataLayer<Akr::LocationLayer>();
    coreInstance.AddDataLayer<Akr::RendererLayer>();
    coreInstance.AddDataLayer<Akr::PhysicsLayer>();

    Akr::Core::GetDataLayer<Akr::InputLayer>()->AddController(std::make_shared<Akr::Input::UIInputControler>());

    return 0;
  };

  static int Cleanup() { return 0; };
};
}  // namespace Akr::Init
