#pragma once

#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/GlBlendMaterialComponent.hpp>

#include <asset/Material.hpp>
#include <asset/Program.hpp>
#include <asset/Vao.hpp>

#include <glm/glm.hpp>

#include <array>

namespace asset
{
    namespace internal
    {
        void init_drawables ();
    }

    namespace drawable
    {    // TODO find a better name for drawable, as it is a render and material component
        [[maybe_unused]] engine::component::GlMaterialComponent create_floor ();
        [[maybe_unused]] engine::component::GlMaterialComponent create_wall_back ();
        [[maybe_unused]] engine::component::GlMaterialComponent create_wall_right ();
        [[maybe_unused]] engine::component::GlMaterialComponent create_wall_front ();
        [[maybe_unused]] engine::component::GlMaterialComponent create_wall_left ();
        [[maybe_unused]] engine::component::GlMaterialComponent create_wall_top ();

        [[maybe_unused]] engine::component::GlMaterialComponent create_player ();

        [[maybe_unused]] engine::component::GlMaterialComponent create_debug_light ();
    }
}
