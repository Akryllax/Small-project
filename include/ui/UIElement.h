#pragma once

#include "IRenderable.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <winnt.h>


namespace Akr::UI {

class DECLSPEC_NOVTABLE UIElement : public IRenderable, public std::enable_shared_from_this<UIElement> {
public:
  enum class State : std::uint8_t { NONE, HOVER, PRESSED, FOCUSED, DISABLED };
  enum class UILayer : std::uint8_t { DEFAULT = 0, FOREGROUND, BACKGROUND, OTHER };
  enum class Type : std::uint8_t {
    UNKNOWN,
    PANEL,
    BUTTON,
    TEXT,
    IMAGE,
    SLIDER,
    SCROLLBAR,
    TEXTBOX,
    CHECKBOX,
    RADIOBUTTON,
    DROPDOWN,
    LISTBOX,
    PROGRESSBAR,
    SPINNER,
    COLORPICKER,
    SEPARATOR,
    CANVAS,
    CUSTOM
  };

  Type type = Type::UNKNOWN;
  State state = State::NONE;
  bool visible = false;
  bool enabled = false;
  bool focused = false;
  bool hovered = false;

  // Modify the constructor to accept an ID and generate one if none is provided.
  UIElement(Type type, std::uint8_t id) : type(type), id(id) {
    if (id == 0) {
      this->id = ++lastAssignedId;
    }
  }

  virtual std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() = 0;

  std::shared_ptr<UIElement> GetParent() const { return parent; }

  std::vector<std::shared_ptr<UIElement>> GetChildren() const { return children; }

  std::shared_ptr<UIElement> GetRoot() {
    if (parent) {
      return parent->GetRoot();
    } else {
      return shared_from_this();
    }
  }

  std::shared_ptr<UIElement> FindElement(std::uint16_t const id) {
    if (this->id == id) {
      return shared_from_this();
    }
    for (auto& child : children) {
      auto found = child->FindElement(id);
      if (found) {
        return found;
      }
    }
    return nullptr;
  }

  std::vector<std::shared_ptr<UIElement>> FindElements(std::uint16_t const id) {
    std::vector<std::shared_ptr<UIElement>> foundElements;
    if (this->id == id) {
      foundElements.push_back(shared_from_this());
    }
    for (auto& child : children) {
      auto found = child->FindElements(id);
      foundElements.insert(foundElements.end(), found.begin(), found.end());
    }
    return foundElements;
  }

  void Traverse(std::function<void(std::shared_ptr<UIElement>)> callback) {
    callback(shared_from_this());
    for (auto& child : children) {
      child->Traverse(callback);
    }
  }

private:
  static inline std::uint16_t lastAssignedId = 0;

  std::uint16_t id;
  std::shared_ptr<UIElement> parent;
  std::vector<std::shared_ptr<UIElement>> children;
};

}  // namespace Akr::UI