#pragma once

#include <stdexcept>
#include <string>
#include <unordered_set>

namespace Akr::Common {

class UniqueString : public std::string {
public:
  UniqueString() = default;
  ~UniqueString() = default;

  // Constructor that ensures uniqueness
  explicit UniqueString(std::string const& str) {
    if (!isUnique(str)) {
      throw std::invalid_argument("String is not unique");
    }
    this->assign(str);
    uniqueStrings.insert(*this);
  }

  // Deleted copy constructor and assignment operator
  UniqueString(UniqueString const&) = delete;
  UniqueString& operator=(UniqueString const&) = delete;

private:
  // Static set to store unique strings
  inline static std::unordered_set<std::string> uniqueStrings;

  // Check if the string is unique
  bool isUnique(std::string const& str) const { return uniqueStrings.find(str) == uniqueStrings.end(); }
};

}  // namespace Akr::Common
