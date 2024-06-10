#pragma once

#include "Dev.h"
#include "EventTypes.h"
#include "IEvent.h"
#include "IEventListener.h"
#include <memory>
#include <vector>

namespace Akr::Core {
template <typename T, typename = std::enable_if_t<std::is_enum_v<T> && std::is_same_v<T, EventTypes>>>
class EventDispatcher {
public:
  static EventDispatcher<T>& GetInstance() {
    static EventDispatcher<T> instance;
    return instance;
  }

  EventDispatcher() = default;
  virtual ~EventDispatcher() = default;

  virtual void AddListener(std::shared_ptr<Common::IEventListener<T>> _listener) {
    // Add listener to the list of listeners
    listeners_.push_back(_listener);
  };
  virtual void RemoveListener(std::shared_ptr<Common::IEventListener<T>>& _listener) {
    // Find the listener in the list
    auto it = std::find(listeners_.begin(), listeners_.end(), _listener);
    if (it != listeners_.end()) {
      // Remove the listener from the list
      listeners_.erase(it);
    }
  };
  virtual void DispatchEvent(std::shared_ptr<Common::IEvent<T>> _event) {
    // Notify all listeners
    for (auto& listener : listeners_) {
      listener->OnEvent(_event);
    }
  };

private:
  // List of listeners
  std::vector<std::shared_ptr<Common::IEventListener<T>>> listeners_;
};

}  // namespace Akr::Core