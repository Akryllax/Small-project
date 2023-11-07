#pragma once

#include <any>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class UniqueIdentifier : public std::string {
 public:
  UniqueIdentifier(std::string const& str) : std::string(str) {
    if (IsDuplicate()) {
      throw std::invalid_argument("String must be unique.");
    }
  }

  void AssociateObject(std::shared_ptr<std::any> obj) {
    associatedObject_ = obj;
  }

  static std::shared_ptr<std::any> GetAssociatedObject(
      UniqueIdentifier const& str) {
    auto it = associatedObjects_.find(str);
    if (it != associatedObjects_.end()) {
      return it->second;
    }
    return nullptr;
  }

 private:
  bool IsDuplicate() const {
    return associatedObjects_.find(*this) != associatedObjects_.end();
  }

  std::shared_ptr<std::any> associatedObject_;
  static std::unordered_map<UniqueIdentifier, std::shared_ptr<std::any>,
                            std::hash<std::string>>
      associatedObjects_;
};