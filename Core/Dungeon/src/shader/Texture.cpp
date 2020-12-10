#include <GL/glew.h>
#include <GL/GL.h>

#include <shader/Texture.hpp>
#include <shader/Util.hpp>

namespace shader
{
    GLuint load_texture (void *texture_source, GLsizei width, GLsizei height)
    {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_source);

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
