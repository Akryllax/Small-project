#pragma once

#include "DataLayer.h"
#include "World.h"
#include <cassert>

namespace Akr {

/**
 * @brief PhysicsLayer class representing a layer responsible for physics simulation.
 */
class PhysicsLayer : public DataLayer {
public:
    Akr::World world; /**< Instance of the world for physics simulation. */

    /**
     * @brief Executes the physics simulation for the given time delta.
     * @param delta The time delta for the simulation.
     */
    void Tick(std::chrono::milliseconds const& delta) override {
        this->GetBox2DWorld().Step(static_cast<float>(delta.count()) * 0.001f, 6, 2);
    }

    /**
     * @brief Retrieves the Box2D world for physics simulation.
     * @return Reference to the Box2D world.
     */
    b2World& GetBox2DWorld() { return this->world.GetBox2DWorld(); }
};

}  // namespace Akr
