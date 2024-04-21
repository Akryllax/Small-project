#pragma once

namespace Akr::Game {
class ISelectable {
public:
  virtual void OnSelect() {};
  virtual void OnDeselect() {};

  void Select() { OnSelect(); }
  void Deselect() { OnDeselect(); }
  virtual ~ISelectable() = default;
};
}  // namespace Akr::Game