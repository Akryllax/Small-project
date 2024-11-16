#pragma once

#include <cstddef>
#include <utility>
#include <vector>
#include <stdexcept>


namespace Akr::Util {

template <typename T>
class IndexedVector {
  using IndexValuePair = std::pair<size_t, T>;

public:
  using iterator = typename std::vector<IndexValuePair>::iterator;
  using const_iterator = typename std::vector<IndexValuePair>::const_iterator;

  IndexedVector() = default;

  void emplace_back(T&& value) { vector_.emplace_back(nextIndex_++, std::forward<T>(value)); }

  void emplace_back(T const& value) { vector_.emplace_back(nextIndex_++, value); }

  void push_back(T&& value) { emplace_back(std::forward<T>(value)); }

  void push_back(T const& value) { emplace_back(value); }

  void erase(iterator const& it) { vector_.erase(it); }

  iterator begin() { return vector_.begin(); }

  iterator end() { return vector_.end(); }

  const_iterator begin() const { return vector_.begin(); }

  const_iterator end() const { return vector_.end(); }

  size_t size() const { return vector_.size(); }

  T& operator[](size_t index) {
    for (auto& [idx, value] : vector_) {
      if (idx == index) {
        return value;
      }
    }
    throw std::out_of_range("Index out of range");
  }

  T const& operator[](size_t index) const {
    for (auto const& [idx, value] : vector_) {
      if (idx == index) {
        return value;
      }
    }
    throw std::out_of_range("Index out of range");
  }

private:
  std::vector<IndexValuePair> vector_;
  size_t nextIndex_ = 0;
};  // class ind_vector
}  // namespace Akr::Util