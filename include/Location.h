#pragma once

#include "Vector2D.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace Akr {

class Location {
 public:
  Location() : position_(0, 0), parent_(nullptr) {}

  Location(Vector2D<float> const& position)
      : position_(position), parent_(nullptr) {}

  Location(long x, long y)
      : position_(Vector2D<float>(x, y)), parent_(nullptr) {}

  Vector2D<float> const& getPosition() const { return position_; }

  void setPosition(Vector2D<float> const& position) {
    if (position == Vector2D<float>(0, 0)) {
      if (parent_ != nullptr) {
        // Position (0,0) is reserved for the root, so it cannot be set if there
        // is a parent.
        throw std::invalid_argument(
            "Position (0,0) is reserved for the root location.");
      }
    }
    position_ = position;
  }

  void setPosition(float x, float y) { setPosition({x, y}); }

  std::shared_ptr<Location> getParent() const { return parent_; }

  void setParent(std::shared_ptr<Location> parent) { parent_ = parent; }

  void addChild(std::shared_ptr<Location> child) { children_.push_back(child); }

  std::vector<std::shared_ptr<Location>> const& getChildren() const {
    return children_;
  }

  // Member function to add another Location to this Location
  Location operator+(Location const& other) const {
    Location result(*this);  // Create a copy of this Location
    result.position_ = this->position_ + other.position_;
    return result;
  }

  // Add other methods or properties as needed.

 private:
  Vector2D<float> position_;
  std::shared_ptr<Location> parent_;
  std::vector<std::shared_ptr<Location>> children_;
};

}  // namespace Akr
