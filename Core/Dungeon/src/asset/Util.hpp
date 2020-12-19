#pragma once

#include <span>
#include <string_view>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdint>

namespace asset::util
{
    GLuint compile_vertex_shader (std::string_view vertex_shader_source);
    GLuint compile_fragment_shader (std::string_view fragment_shader_source);
    GLuint compile_program (GLuint vertex_shader, GLuint fragment_shader);

    GLuint generate_vao(std::span<glm::vec3> points, std::span<uint32_t> indices, std::span<glm::vec3> normals, std::span<glm::vec2> tex_coords);

    GLuint load_texture (void *texture_source, GLsizei width, GLsizei height);
    GLuint load_texture_skybox (void *texture_source, GLsizei width, GLsizei height);

    bool check_error ();
    bool check_fbo_error ();
}
