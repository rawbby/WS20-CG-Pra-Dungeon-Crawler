#include <GL/glew.h>
#include <GL/GL.h>

#include <shader/Program.hpp>
#include <vector>
#include <spdlog/spdlog.h>

namespace
{
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

            spdlog::error("OPENGL SHADER COMPILATION FAILED! log: ", info_log.data());

            glDeleteShader(shader);
            return GL_NONE;
        }

        return shader;
    }
}

namespace shader
{
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

            auto info_log = std::vector<GLchar> (info_log_length);
            glGetProgramInfoLog(program, info_log_length, &info_log_length, info_log.data());

            spdlog::error("OPENGL PROGRAM LINK FAILED! log: ", info_log.data(), __FILE__, __LINE__);

            glDeleteProgram(program);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            return GL_NONE;
        }

        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);

        return program;
    }
}
