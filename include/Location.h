#include "Vector2D.h"
#include <stdexcept>
#include <vector>

namespace Akr {

class Location {
 public:
  Location() : position_(0, 0), parent_(nullptr) {}

  Location(Vector2D<long> const& position)
      : position_(position), parent_(nullptr) {}

  Vector2D<long> const& getPosition() const { return position_; }

  void setPosition(Vector2D<long> const& position) {
    if (position == Vector2D<long>(0, 0)) {
      if (parent_ != nullptr) {
        // Position (0,0) is reserved for the root, so it cannot be set if there
        // is a parent.
        throw std::invalid_argument(
            "Position (0,0) is reserved for the root location.");
      }
    }
    position_ = position;
  }

  void setPosition(long x, long y)
  {
    setPosition({x,y});
  }

  Location* getParent() const { return parent_; }

  void setParent(Location* parent) { parent_ = parent; }

  void addChild(Location* child) { children_.push_back(child); }

  std::vector<Location*> const& getChildren() const { return children_; }

  // Add other methods or properties as needed.

 private:
  Vector2D<long> position_;
  Location* parent_;
  std::vector<Location*> children_;
};

}  // namespace Akr
