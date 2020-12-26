#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Material.hpp>

#include <geometries/PlaneBottom.hpp>

#include <QImage>
#include <string_view>

#define asset_material_init_material(material, vendor, name) \
        material.tex_basecolor = texture_from_path(":/materials/" vendor "/" name "_basecolor.png"); \
        material.tex_height    = texture_from_path(":/materials/" vendor "/" name "_height.png"); \
        material.tex_mrao      = texture_from_path(":/materials/" vendor "/" name "_mrao.png"); \
        material.tex_normal    = texture_from_path(":/materials/" vendor "/" name "_normal.png")

namespace
{
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

        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error("OPENGL ERROR! (FILE: \"{}\", LINE: \"{}\")\n{}", __FILE__, __LINE__, status);

            glDeleteTextures(1, &texture);
            return GL_NONE;
        }

        return texture;
    }

    /* GLuint load_texture_skybox (void *texture_source, GLsizei width, GLsizei height)
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

        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error("OPENGL ERROR! (FILE: \"{}\", LINE: \"{}\")\n{}", __FILE__, __LINE__, status);

            glDeleteTextures(1, &texture);
            return GL_NONE;
        }

        return texture;
    } */

    GLuint texture_from_path (std::string_view path)
    {   // TODO workaround used! copied QGLWidget's convertToGlFormat function from Qt5 wich is not supported anymore.

        using namespace asset;

        auto qt_image = QImage(QString(path.data()));
        qt_image.convertTo(QImage::Format_ARGB32);

        QImage gl_image(qt_image.size(), QImage::Format_ARGB32);

        const auto width = qt_image.width();
        const auto height = qt_image.height();

        auto p = reinterpret_cast<const uint *> (qt_image.scanLine(qt_image.height() - 1));
        auto q = reinterpret_cast<uint *> (gl_image.scanLine(0));

        for (int i = 0; i < height; ++i)
        {
            const uint *end = p + width;
            while (p < end)
            {
                *q = ((*p << 16) & 0xff0000) | ((*p >> 16) & 0xff) | (*p & 0xff00ff00);
                ++p;
                ++q;
            }
            p -= 2 * width;
        }

        return load_texture(gl_image.bits(), gl_image.width(), gl_image.height());
    }
}

namespace asset::internal
{
    void init_materials ()
    {
        asset_material_init_material(asset::material::pile_of_skulls, "gametextures", "PileOfSkulls");
        asset_material_init_material(asset::material::black_granite, "gametextures", "BlackGranite");
        asset_material_init_material(asset::material::broken_limestone_brick_path, "gametextures", "BrokenLimestoneBrickPath");
    }
}
