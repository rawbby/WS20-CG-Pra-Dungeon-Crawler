#pragma once

#include <glm/glm.hpp>

namespace engine
{
    inline glm::vec3 fromCoordinate (glm::vec2 coordinate, float height = 0.0f)
    {
        return {coordinate.x, height, -coordinate.y};
    }

    inline glm::vec2 toCoordinate (glm::vec3 position)
    {
        return {position.x, -position.z};
    }

    inline float toHeight (glm::vec3 position)
    {
        return position.y;
    }
}
