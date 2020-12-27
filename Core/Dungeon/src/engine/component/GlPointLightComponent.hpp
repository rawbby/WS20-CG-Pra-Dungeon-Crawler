#pragma once

#include <glm/vec3.hpp>

namespace engine::component
{
    /**
     * Needed input for OpenGl to render a point light.
     */
    struct GlPointLightComponent
    {
        glm::vec3 color{};
        float height = 0.5f;
    };
}
