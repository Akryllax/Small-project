#pragma once

#include "box2d/b2_math.h"
namespace Akr::Math {

struct Rect {
  float x;
  float y;
  float w;
  float h;
  float angle;

  /*
   * @brief Get the parent's Rect, and taking into account the width and height of the child's Rect, return a new position of the Child
   * rect, that keeps it's size but has a centerer position in the father.
   */
  static Rect GetCenteredRect(Rect const& parentRect, Rect const& childRect) {
    Rect centeredRect;

    // Calculate new position to center the child rectangle within the parent rectangle
    centeredRect.x = parentRect.x + (parentRect.w - childRect.w) / 2;
    centeredRect.y = parentRect.y + (parentRect.h - childRect.h) / 2;
    centeredRect.w = childRect.w;
    centeredRect.h = childRect.h;
    centeredRect.angle = childRect.angle;

    return centeredRect;
  };

  Rect operator+(b2Vec2 const& vec) { return Rect{x + vec.x, y + vec.y, w, h, angle}; };
};
}  // namespace Akr::Math