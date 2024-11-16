#pragma once

#include "Rect.h"
namespace Akr::Game {
class ISelectable {
public:
  virtual bool OnSelect() { return true; }
  virtual bool OnDeselect() { return true;}

  void Select() { if(OnSelect()) SetSelected(this); }
  void Deselect() { if(OnDeselect()) SetSelected(nullptr); }
  virtual ~ISelectable() = default;

  static ISelectable* GetSelected() { return selected_; }
  static void SetSelected(ISelectable* selected) { selected_ = selected; }

protected:
  static inline ISelectable* selected_ = nullptr;
  Akr::Math::Rect uiBoundingRect_;

};
}  // namespace Akr::Game