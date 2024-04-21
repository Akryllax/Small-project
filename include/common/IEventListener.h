#pragma once

#include "IEvent.h"

namespace Akr::Common {
  template <typename T>
    class IEventListener {
    public:
      virtual ~IEventListener() = default;

      virtual void OnEvent(IEvent<T> event) = 0;
    };
}