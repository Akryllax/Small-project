#pragma once

#include "Core.h"
#include "GameLayer.h"
#include "INamedObject.h"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include <memory>
#include <string>
#include <vcruntime_typeinfo.h>
#include <vector>

namespace Akr::Game {

class GObject : public Common::INamedObject, private std::enable_shared_from_this<GObject> {
public:
  GObject();
  GObject(std::string const& name) : Common::INamedObject(name), name_(name){};
  virtual ~GObject() { Core::GetDataLayer<GameLayer>()->UntrackGObject(shared_from_this()); };

  b2Transform const& GetTransform() const;

  std::vector<std::shared_ptr<GObject>>& GetChildren();

  IS_CHILD_OF_TYPE_ARGS_T(GObject)
  static std::shared_ptr<T> make_shared_gobject(Args&&... args) {
    auto sharedPtr = std::make_shared<T>(std::forward<Args>(args)...);

    Core::GetDataLayer<GameLayer>()->TrackGObject(sharedPtr);

    return sharedPtr;
  }

private:
  std::string name_;
  std::shared_ptr<GObject> parent_;
  std::vector<std::shared_ptr<GObject>> children_;
  b2Body* body_;
  b2BodyDef bodyDef_;

  // Protect from accidental copy
  GObject(GObject const&) = delete;
};

}  // namespace Akr::Game
