#pragma once

#include <string>
namespace Akr::Common {
using NamedString = std::string;

class INamedObject {
public:
  INamedObject(std::string name) : name_(name) {}

  inline std::string GetName() const { return name_; }
  inline void SetName(std::string const name) { name_ = name; };

private:
  std::string name_;
};

// By default, use std::string
}  // namespace Akr::Common
