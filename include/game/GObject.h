#pragma once

#include "Core.h"
#include "PhysicsLayer.h"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include "spdlog.h"
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Akr::Game {

class GObject : private std::enable_shared_from_this<GObject> {
public:
    GObject();
    explicit GObject(std::string const& name);
    virtual ~GObject() = default;

    b2Transform const& GetTransform() const;

    void setName(std::string_view const& newName);
    std::string GetName() const;

    void AddChild(std::shared_ptr<GObject> newChild);
    std::shared_ptr<GObject> GetChildGObject(std::string_view const& name);

    std::vector<std::shared_ptr<GObject>>& GetChildren();

private:
    std::string name_;
    std::shared_ptr<GObject> parent_;
    std::vector<std::shared_ptr<GObject>> children_;
    b2Body* body_;
    b2BodyDef bodyDef_;

    // Protect from accidental copy
    GObject(const GObject&) = delete;
};

} // namespace Akr::Game