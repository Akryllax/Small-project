#pragma once

#include <new>
#include <type_traits>

namespace Akr::Common {
// Type trait to check if T is derived from DataLayer
template <typename T, typename V>
struct IsDerivedFromV {
  static constexpr bool value = std::is_base_of_v<V, T>;
};
}  // namespace Akr::Common