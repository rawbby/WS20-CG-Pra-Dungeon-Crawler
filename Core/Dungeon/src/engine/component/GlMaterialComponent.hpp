#pragma once

#include <engine/component/GlRenderComponent.hpp>

namespace engine::component
{
    struct Material
    {
        GLuint tex_basecolor = GL_NONE;
        GLuint tex_height = GL_NONE;
        GLuint tex_mrao = GL_NONE;
        GLuint tex_normal = GL_NONE;
    };

    /**
     * Needed textures for OpenGl to render a material
     */
    struct GlMaterialComponent
            : public GlRenderComponent
    {
        Material material;
    };
}
