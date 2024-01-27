#pragma once

#include "box2d/b2_math.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace Akr {

class Location {
 public:
  Location() : position_(0, 0), parent_(nullptr) {}

  Location(b2Vec2 const& position) : position_(position), parent_(nullptr) {}

  Location(long x, long y) : position_(b2Vec2(x, y)), parent_(nullptr) {}

  b2Vec2 const& getPosition() const { return position_; }

  void setPosition(b2Vec2 const& position) {
    if (position == b2Vec2(0, 0)) {
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
  b2Vec2 position_;
  std::shared_ptr<Location> parent_;
  std::vector<std::shared_ptr<Location>> children_;
};

}  // namespace Akr
