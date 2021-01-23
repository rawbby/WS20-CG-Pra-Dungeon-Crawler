#pragma once

#include <glm/glm.hpp>

namespace engine::component
{
    /**
     * Circle bounding box.
     * Used for all dynamic collision components.
     *
     * Entities with this component also
     * need to have the PositionComponent
     * to be used with the CollisionService.
     */
    struct DynamicCollisionCircle
    {
        glm::vec2 velocity{};
        float radius = 0.0f;
    };
}
