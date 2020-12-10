#pragma once

#include <string_view>

namespace shader
{
    GLuint load_texture (void *texture_source, GLsizei width, GLsizei height);
    GLuint load_texture_skybox (void *texture_source, GLsizei width, GLsizei height);
}
