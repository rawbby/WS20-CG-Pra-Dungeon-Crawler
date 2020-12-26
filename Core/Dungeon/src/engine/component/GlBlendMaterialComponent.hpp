#pragma once

#include <array>

namespace engine::component
{
    /**
     * Needed textures for OpenGl to render a object
     * with multiple materials.
     * Up to three materials are supported.
     */
    struct GlBlendMaterialComponent
    {
        std::array <struct {
            GLuint tex_basecolor = GL_NONE;
            GLuint tex_height = GL_NONE;
            GLuint tex_mrao = GL_NONE;
            GLuint tex_normal = GL_NONE;
        }> materials[3];
        GLuint tex_blend = GL_NONE;
    };
}
