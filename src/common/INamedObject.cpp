#include "INamedObject.h"
#include "Core.h"
#include "NamedLayer.h"

namespace Akr::Common {

INamedObject::INamedObject(std::string name) : name_(std::move(name)) {}

std::string INamedObject::GetName() const { return name_; }

void INamedObject::SetName(std::string name) { name_ = std::move(name); }

}  // namespace Akr::Common