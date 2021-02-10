#pragma once

#include <glm/glm.hpp>

namespace engine::component
{
    /**
     * Needed input for OpenGl to render a point light.
     */
    struct GlPointLightComponent
    {
        glm::vec3 color{};
        float height = 0.0f;
        GLuint program = GL_NONE;
        GLuint program_ani = GL_NONE;

        // TODO save width and height
        GLuint tex_shadow = GL_NONE;
    };
}
