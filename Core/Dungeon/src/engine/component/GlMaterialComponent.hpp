#pragma once

namespace engine::component
{
    /**
     * Needed textures for OpenGl to render a material
     */
    struct GlMaterialComponent
    {
        GLuint tex_basecolor = GL_NONE;
        GLuint tex_height = GL_NONE;
        GLuint tex_mrao = GL_NONE;
        GLuint tex_normal = GL_NONE;
    };
}
