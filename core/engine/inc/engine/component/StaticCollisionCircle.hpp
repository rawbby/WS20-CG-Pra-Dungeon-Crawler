#pragma once

#include <glm/glm.hpp>

namespace engine::component
{
    /**
     * Axis aligned bounding box.
     * Used for all static collision components.
     *
     * Entities with this component also
     * need to have the PositionComponent
     * to be used with the CollisionService.
     */
    struct StaticCollisionCircle
    {
        glm::vec2 position{};
        float radius = 0.0f;
    };
}
