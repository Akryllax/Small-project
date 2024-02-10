#pragma once

#include <memory>
#include <string>

namespace Akr::Common {

class INamedObject {
public:
  INamedObject(std::string name);
  ~INamedObject();

  std::string GetName() const;
  void SetName(std::string const name);

private:
  std::string name_;
};

// By default, use std::string
}  // namespace Akr::Common
