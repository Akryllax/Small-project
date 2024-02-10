#pragma once

#include <any>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Akr {

class UniqueIdentifier {
 public:
  UniqueIdentifier(std::weak_ptr<std::any> targetObject,
                   std::string const& identifier = "")
      : assignedId_(identifier), associatedPtr_(targetObject){};

 private:
  std::string assignedId_;
  std::weak_ptr<std::any> associatedPtr_;
};

// class UniqueIdentifier : public std::string {
//  public:
//   UniqueIdentifier(std::string const& str) : std::string(str) {
//     if (IsDuplicate(str)) {
//       throw std::invalid_argument("String must be unique: " + str);
//     }
//   }

//   // Declare copy constructor as deleted
//   UniqueIdentifier(const UniqueIdentifier&) = delete;

//   void AssociateObject(std::shared_ptr<std::any> obj) {
//     associatedObject_ = obj;
//   }

//   static std::shared_ptr<std::any> GetAssociatedObject(
//       UniqueIdentifier const& str) {
//     if (auto it = associatedObjects_.find(str);
//         it != associatedObjects_.end()) {
//       return it->second;  // Use lock to convert weak_ptr to
//       shared_ptr
//     }
//     return nullptr;
//   }

//   static void DisassociateObject(UniqueIdentifier const& str) {
//     auto it = associatedObjects_.find(str);
//     if (it != associatedObjects_.end()) {
//       associatedObjects_.erase(it);
//     }
//   }

//   // Static method to generate a random UniqueIdentifier
//   static UniqueIdentifier GenerateRandomIdentifier() {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis('a', 'z');

//     std::string randomStr;
//     for (int i = 0; i < 10; ++i) {
//       randomStr += static_cast<char>(dis(gen));
//     }

//     return UniqueIdentifier(randomStr);
//   }

//  private:
//   static bool IsDuplicate(std::string const& newString) {
//     return associatedObjects_.find(newString) != associatedObjects_.end();
//   }

//   std::shared_ptr<std::any> associatedObject_;
//   static std::unordered_map<std::shared_ptr<UniqueIdentifier>,
//   std::weak_ptr<std::any>,
//                             std::hash<std::string>>
//       associatedObjects_;
// };
}  // namespace Akr