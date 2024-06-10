#pragma once

#include <memory>
namespace Akr::Common
{
  template<typename T>
  class IEvent
  {
  public:
    virtual void NotifyListeners(const T& eventData) = 0;

    void SetData(std::shared_ptr<T> data)
    {
      this->data = data;
    };

  protected:
    std::shared_ptr<T> data_;

  };
} // namespace Akr::Common