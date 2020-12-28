#pragma once

#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>

#include <array>

namespace engine::component
{
    /**
     * Needed textures for OpenGl to render a object
     * with multiple materials.
     * Up to three materials are supported.
     */
    struct GlBlendMaterialComponent
            : public GlRenderComponent
    {
        std::array<Material, 3> materials{};
        GLuint tex_blend = GL_NONE;
    };
}
