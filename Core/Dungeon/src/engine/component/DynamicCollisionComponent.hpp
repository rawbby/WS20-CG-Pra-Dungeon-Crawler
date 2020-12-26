#pragma once

#include <glm/vec2.hpp>

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
    struct DynamicCollisionComponent
    {
        float radius = 0.0f;
        glm::vec2 velocity{};
    };
}
