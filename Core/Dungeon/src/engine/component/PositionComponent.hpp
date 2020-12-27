#pragma once

#include <glm/vec2.hpp>

namespace engine::component
{
    /**
     * 2d position.
     * Used to translate components
     * only on x-axis and y-axis.
     *
     * Also used by the CollisionService
     * to translate the 2d bounding box.
     */
    using PositionComponent = glm::vec2;
}
