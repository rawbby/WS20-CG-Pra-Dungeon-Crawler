#pragma once

// expose interface

#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/GlBlendMaterialComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>

#include <glm/glm.hpp>

#include <array>

namespace asset
{
    namespace internal
    {
        void init_vaos ();
        void init_programs ();
        void init_materials ();
    }

    inline void init_assets ()
    {
        internal::init_vaos();
        internal::init_programs();
        internal::init_materials();
    }

    namespace vao
    {
        inline GLuint plane = GL_NONE;
        inline GLuint plane_lr = GL_NONE;

        inline GLuint sphere = GL_NONE;
        inline GLuint sphere_lr = GL_NONE;

        inline GLsizei plane_count = 0;
        inline GLsizei plane_lr_count = 0;

        inline GLsizei sphere_count = 0;
        inline GLsizei sphere_lr_count = 0;
    }

    namespace program
    {
        inline GLuint trivial{};
        inline GLuint material{};
        inline GLuint pbr{};
        inline GLuint shadow{};
    }

    namespace material
    {
        inline engine::component::Material black_granite{};
        inline engine::component::Material black_ostrich_hide_wrinkles_2{};
        inline engine::component::Material broken_limestone_brick_path{};
        inline engine::component::Material chunky_wet_gravel_and_dirt{};
        inline engine::component::Material clay_01{};
        inline engine::component::Material cracked_red_ceramic_roof{};
        inline engine::component::Material dirty_hammered_copper{};
        inline engine::component::Material pile_of_skulls{};
        inline engine::component::Material white_wool_cloth{};
        inline engine::component::Material wool_woven_carpet_striped_burgundy{};

        engine::component::GlMaterialComponent create_floor ();
        engine::component::GlMaterialComponent create_wall_back ();
        engine::component::GlMaterialComponent create_wall_right ();
        engine::component::GlMaterialComponent create_wall_front ();
        engine::component::GlMaterialComponent create_wall_left ();
        engine::component::GlMaterialComponent create_wall_top ();
        engine::component::GlMaterialComponent create_player ();
        engine::component::GlMaterialComponent create_debug_light ();
    }
}
