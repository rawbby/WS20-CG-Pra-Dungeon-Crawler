#pragma once

#include <string_view>

namespace shader
{
    GLuint compile_vertex_shader (std::string_view vertex_shader_source);
    GLuint compile_fragment_shader (std::string_view fragment_shader_source);
    GLuint compile_program (GLuint vertex_shader, GLuint fragment_shader);
}
