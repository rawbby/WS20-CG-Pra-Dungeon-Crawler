#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Program.hpp>

#include <spdlog/spdlog.h>

#include <QFile>
#include <QTextStream>

#include <string_view>

namespace
{
    std::string load_text (std::string_view path)
    {
        QFile file{path.data()};
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            spdlog::error("QFILE CAN NOT BE OPENED! path: ", path);
            return "";
        }

        auto result = QTextStream{&file}.readAll().toStdString();
        file.close();

        return result;
    }

    GLuint compile_shader (GLuint type, std::string_view shader_source)
    {
        GLuint shader = glCreateShader(type);

        const auto shader_data = shader_source.data();
        glShaderSource(shader, 1, &shader_data, nullptr);

        glCompileShader(shader);

        GLint compile_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

        if (GL_TRUE != compile_status)
        {
            GLint info_log_length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

            auto info_log = std::vector<GLchar>(info_log_length);
            glGetShaderInfoLog(shader, info_log_length, &info_log_length, info_log.data());

            spdlog::error("OPENGL SHADER COMPILATION FAILED! log: {}, source: {}, file: {}, line: {} ", info_log.data(), shader_source, __FILE__, __LINE__);

            glDeleteShader(shader);
            return GL_NONE;
        }

        return shader;
    }

    GLuint compile_vertex_shader (std::string_view vertex_shader_source)
    {
        return compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    }

    GLuint compile_fragment_shader (std::string_view fragment_shader_source)
    {
        return compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    }

    GLuint compile_program (GLuint vertex_shader, GLuint fragment_shader)
    {
        GLuint program = glCreateProgram();

        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);

        glLinkProgram(program);

        GLint link_status;
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (GL_TRUE != link_status)
        {
            GLint info_log_length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

            auto info_log = std::vector<GLchar>(info_log_length);
            glGetProgramInfoLog(program, info_log_length, &info_log_length, info_log.data());

            spdlog::error("OPENGL PROGRAM LINK FAILED! log: {}, file {}, line {}", info_log.data(), __FILE__, __LINE__);

            glDeleteProgram(program);
            return GL_NONE;
        }

        return program;
    }

    GLuint vertex_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return compile_vertex_shader(load_text(path));
    }

    GLuint fragment_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return compile_fragment_shader(load_text(path));
    }
}

namespace asset::internal
{
    void init_programs ()
    {
        const auto material_vertex_shader = vertex_shader_from_path(":/glsl/Material.vs.glsl");
        const auto trivial_vertex_shader  = vertex_shader_from_path(":/glsl/Trivial.vs.glsl");

        const auto material_fragment_shader    = fragment_shader_from_path(":/glsl/Material.fs.glsl");
        const auto trivial_red_fragment_shader = fragment_shader_from_path(":/glsl/TrivialRed.fs.glsl");

        program::material = compile_program(material_vertex_shader, material_fragment_shader);
        program::trivial  = compile_program(trivial_vertex_shader, trivial_red_fragment_shader);

        glDeleteShader(material_vertex_shader);
        glDeleteShader(trivial_vertex_shader);

        glDeleteShader(material_fragment_shader);
        glDeleteShader(trivial_red_fragment_shader);

        const auto debug_matterial_program = program::material;
        const auto debug_trivial_program = program::trivial;
    }
}
