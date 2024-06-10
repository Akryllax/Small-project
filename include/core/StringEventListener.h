#pragma once

#include "IEvent.h"
#include "IEventListener.h"

namespace Akr::Core {
    class StringEventListener : public Akr::Common::IEventListener<std::string>{
    public:
      ~StringEventListener() override = default;

      void OnEvent(Akr::Common::IEvent<std::string> event) override = 0;
    };
}