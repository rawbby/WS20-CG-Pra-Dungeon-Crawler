#pragma once

#include <glm/mat4x4.hpp>

struct TrivialDrawable
{
    GLuint    program = GL_NONE;
    GLuint    vbo     = GL_NONE;
    GLsizei   count   = 0;
    glm::mat4 model_view_matrix{};
};

struct SingleTextureDrawable
        : public TrivialDrawable
{
    GLuint texture = GL_NONE;
};
