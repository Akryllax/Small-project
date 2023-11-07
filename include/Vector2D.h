#pragma once

#include <cmath>
namespace Akr {

template <typename T>
class Vector2D {
 public:
  T x;
  T y;

  // Constructors
  Vector2D() : x(0), y(0) {}
  Vector2D(T xVal, T yVal) : x(xVal), y(yVal) {}

  // Copy constructor
  Vector2D(Vector2D const& other) : x(other.x), y(other.y) {}

  // Assignment operator
  Vector2D& operator=(Vector2D const& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  // Vector addition
  Vector2D operator+(Vector2D const& other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  // Vector subtraction
  Vector2D operator-(Vector2D const& other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  // Scalar multiplication
  Vector2D operator*(T scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  // Dot product
  T dot(Vector2D const& other) const { return x * other.x + y * other.y; }

  // Cross product (for 2D, it's not a true cross product but a scalar value)
  T cross(Vector2D const& other) const { return x * other.y - y * other.x; }

  // Magnitude (length) of the vector
  T magnitude() const { return std::sqrt(x * x + y * y); }

  // Normalize the vector
  Vector2D normalize() const {
    T mag = magnitude();
    if (mag != 0) {
      return Vector2D(x / mag, y / mag);
    }
    return *this;  // Avoid division by zero
  }

  // Check if two vectors are equal
  bool operator==(Vector2D const& other) const {
    return x == other.x && y == other.y;
  }

  // Check if two vectors are not equal
  bool operator!=(Vector2D const& other) const { return !(*this == other); }
};
}  // namespace Akr