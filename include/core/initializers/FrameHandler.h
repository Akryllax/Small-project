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
class FrameManager {
public:
  static int Initialize(Akr::Core& coreInstance) {
    return 0;
  }

  static int RunMainLoop(Akr::Core& coreInstance)
  {
    return 0;
  };

  static int Cleanup() {
    return 0;
  }
};
}  // namespace Akr::Init