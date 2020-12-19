#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Util.hpp>
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

            spdlog::error("OPENGL SHADER COMPILATION FAILED! log: {}, source: {}, file: {}, line: {} ", info_log.data(), shader_source, __FILE__, __LINE__);

            glDeleteShader(shader);
            return GL_NONE;
        }

        return shader;
    }
}

namespace asset::util
{
    bool check_error ()
    {
        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error("OPENGL ERROR! status: ", status);
            return false;
        }
        return true;
    }

    bool check_fbo_error ()
    {
        const auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (GL_FRAMEBUFFER_COMPLETE != status)
        {
            spdlog::error("OPENGL UNCOMPLETE FRAMEBUFFER! status: ", status);
            return false;
        }
        return true;
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

    GLuint generate_vao(std::span<glm::vec3> points, std::span<uint32_t> indices, std::span<glm::vec3> normals, std::span<glm::vec2> tex_coords)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        GLuint pointsBuffer;
        glGenBuffers(1, &pointsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        GLuint normalsBuffer;
        glGenBuffers(1, &normalsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        GLuint texCoordsBuffer;
        glGenBuffers(1, &texCoordsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
        glBufferData(GL_ARRAY_BUFFER, tex_coords.size() * sizeof(glm::vec2), tex_coords.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2);

        GLuint indicesBuffer;
        glGenBuffers(1, &indicesBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(GL_NONE);
        glDeleteBuffers(1, &pointsBuffer);
        glDeleteBuffers(1, &texCoordsBuffer);
        glDeleteBuffers(1, &indicesBuffer);
        glDeleteBuffers(1, &normalsBuffer);

        if (check_error())
        {
            return vao;
        }

        glDeleteVertexArrays(1, &vao);
        return GL_NONE;
    }

    GLuint load_texture (void *texture_source, GLsizei width, GLsizei height)
    {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if (check_error())
        {
            return texture;
        }

        glDeleteTextures(1, &texture);
        return GL_NONE;
    }

    GLuint load_texture_skybox (void *texture_source, GLsizei width, GLsizei height)
    {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        if (check_error())
        {
            return texture;
        }

        glDeleteTextures(1, &texture);
        return GL_NONE;
    }
}
