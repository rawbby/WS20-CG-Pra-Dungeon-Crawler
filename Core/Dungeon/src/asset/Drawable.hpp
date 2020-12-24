#pragma once

#include <asset/Material.hpp>
#include <asset/Mvm.hpp>
#include <asset/Program.hpp>
#include <asset/Vao.hpp>

#include <glm/mat4x4.hpp>
#include <glm/common.hpp>

#include <array>

namespace asset
{
    namespace internal
    {
        void init_drawables ();
    }

    struct TrivialDrawable
    {
        GLuint    program = GL_NONE;
        GLuint    vao     = GL_NONE;
        GLsizei   count   = 0;
        glm::mat4 model_view_matrix{}; // builds identity
    };

    struct MaterialDrawable
            : public TrivialDrawable
            , public Material
    {
    };

    /* struct BlendMaterialDrawable
            : public TrivialDrawable
    {
        std::array<Material, 3> materials{};
        GLuint                  tex_blend = GL_NONE;
    }; */

    namespace drawable
    {
        [[maybe_unused]] MaterialDrawable create_floor ();
        [[maybe_unused]] MaterialDrawable create_wall_back ();
        [[maybe_unused]] MaterialDrawable create_wall_right ();
        [[maybe_unused]] MaterialDrawable create_wall_front ();
        [[maybe_unused]] MaterialDrawable create_wall_left ();
        [[maybe_unused]] MaterialDrawable create_wall_top ();
    }
}
