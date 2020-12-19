#pragma once

#include <glm/mat4x4.hpp>

namespace asset
{
    struct TrivialDrawable
    {
        GLuint  program = GL_NONE;
        GLuint  vao     = GL_NONE;
        GLsizei count   = 0;
        glm::mat4 model_view_matrix{};
    };

    struct MaterialDrawable
            : public TrivialDrawable
    {
        GLuint tex_basecolor = GL_NONE;
        GLuint tex_height    = GL_NONE;
        GLuint tex_mrao      = GL_NONE;
        GLuint tex_normal    = GL_NONE;
    };
}
