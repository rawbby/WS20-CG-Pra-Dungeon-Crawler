#include <GL/glew.h>
#include <GL/GL.h>

#include <shader/Assets.hpp>
#include <common/FileUtil.hpp>
#include <shader/Texture.hpp>
#include <shader/Program.hpp>
#include <shader/Util.hpp>

namespace
{
    GLuint vertex_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return shader::compile_vertex_shader(common::load_text(path));
    }

    GLuint fragment_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return shader::compile_fragment_shader(common::load_text(path));
    }
}

namespace shader
{
    namespace vertex_shader
    {
        [[maybe_unused]] extern GLuint trivial = GL_NONE;
    }
    namespace fragment_shader
    {
        [[maybe_unused]] extern GLuint trivial_red = GL_NONE;
    }
    namespace texture
    {
    }

    void load_assets ()
    {
        vertex_shader::trivial       = vertex_shader_from_path(":/glsl/trivial.vs.glsl");
        fragment_shader::trivial_red = fragment_shader_from_path(":/glsl/trivial_red.fs.glsl");
    }
}
