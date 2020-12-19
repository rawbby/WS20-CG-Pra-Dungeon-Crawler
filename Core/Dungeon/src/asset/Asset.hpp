#pragma once

#include <asset/Drawable.hpp>

namespace asset
{
    namespace program
    {
        [[maybe_unused]] inline GLuint trivial;
        [[maybe_unused]] inline GLuint material;
    }

    namespace material
    {
        [[maybe_unused]] inline GLuint pile_of_skulls_basecolor;
        [[maybe_unused]] inline GLuint pile_of_skulls_emissive;
        [[maybe_unused]] inline GLuint pile_of_skulls_height;
        [[maybe_unused]] inline GLuint pile_of_skulls_mrao;
        [[maybe_unused]] inline GLuint pile_of_skulls_normal;
        [[maybe_unused]] inline GLuint pile_of_skulls_opacity;

        [[maybe_unused]] inline GLuint black_granite_basecolor;
        [[maybe_unused]] inline GLuint black_granite_emissive;
        [[maybe_unused]] inline GLuint black_granite_height;
        [[maybe_unused]] inline GLuint black_granite_mrao;
        [[maybe_unused]] inline GLuint black_granite_normal;
        [[maybe_unused]] inline GLuint black_granite_opacity;

        [[maybe_unused]] inline GLuint broken_limestone_brick_path_basecolor;
        [[maybe_unused]] inline GLuint broken_limestone_brick_path_emissive;
        [[maybe_unused]] inline GLuint broken_limestone_brick_path_height;
        [[maybe_unused]] inline GLuint broken_limestone_brick_path_mrao;
        [[maybe_unused]] inline GLuint broken_limestone_brick_path_normal;
        [[maybe_unused]] inline GLuint broken_limestone_brick_path_opacity;
    }

    namespace drawable
    {
        [[maybe_unused]] MaterialDrawable create_floor ();
        [[maybe_unused]] MaterialDrawable create_wall_back ();
        [[maybe_unused]] MaterialDrawable create_wall_right ();
        [[maybe_unused]] MaterialDrawable create_wall_front ();
        [[maybe_unused]] MaterialDrawable create_wall_left ();
        [[maybe_unused]] MaterialDrawable create_wall_top ();
    }

    void load_assets ();
}
