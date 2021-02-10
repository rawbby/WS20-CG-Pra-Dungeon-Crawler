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
        glm::vec2 direction_norm{1.0f, 0.0f};
        float speed = 0.0f;
        float radius = 0.0f;

        [[nodiscard]] inline glm::vec2 velocity () const noexcept
        {
            return direction_norm * speed;
        }

        inline void velocity (glm::vec2 v)
        {
            speed = glm::length(v);
            direction_norm = (speed == 0.0f) ? direction_norm : glm::normalize(v);
        }

        inline void direction (glm::vec2 v)
        {
            direction_norm = (glm::length(v) == 0.0f) ? direction_norm : glm::normalize(v);
        }
    };
}
