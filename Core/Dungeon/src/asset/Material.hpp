#pragma once

namespace asset
{
    namespace internal
    {
        void init_materials ();
    }

    struct Material
    {
        GLuint tex_basecolor = GL_NONE;
        GLuint tex_height    = GL_NONE;
        GLuint tex_mrao      = GL_NONE;
        GLuint tex_normal    = GL_NONE;
    };

    namespace material
    {
        [[maybe_unused]] inline Material pile_of_skulls{};
        [[maybe_unused]] inline Material black_granite{};
        [[maybe_unused]] inline Material broken_limestone_brick_path{};
    }
}
