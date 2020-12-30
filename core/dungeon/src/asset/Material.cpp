#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Material.hpp>

#include <resource/PbrMaterial.hpp>

#include <string_view>

namespace
{
    GLuint load_texture (void *texture_source, GLsizei width, GLsizei height, GLuint format = GL_RGBA)
    {
        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texture_source);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error(R"(OPENGL ERROR! (FILE: "{}", LINE: "{}", STATUS: "{}"))", __FILE__, __LINE__, status);

            glDeleteTextures(1, &texture);
            return GL_NONE;
        }

        return texture;
    }

//    GLuint texture_from_path (std::string_view path)
//    {   // TODO workaround used! copied QGLWidget's convertToGlFormat function from Qt5 wich is not supported anymore.
//
//        using namespace asset;
//
//        auto qt_image = QImage(QString(path.data()));
//        qt_image.convertTo(QImage::Format_ARGB32);
//
//        QImage gl_image(qt_image.size(), QImage::Format_ARGB32);
//
//        const auto width = qt_image.width();
//        const auto height = qt_image.height();
//
//        auto p = reinterpret_cast<const uint *> (qt_image.scanLine(qt_image.height() - 1));
//        auto q = reinterpret_cast<uint *> (gl_image.scanLine(0));
//
//        for (int i = 0; i < height; ++i)
//        {
//            const uint *end = p + width;
//            while (p < end)
//            {
//                *q = ((*p << 16) & 0xff0000) | ((*p >> 16) & 0xff) | (*p & 0xff00ff00);
//                ++p;
//                ++q;
//            }
//            p -= 2 * width;
//        }
//
//        return load_texture(gl_image.bits(), gl_image.width(), gl_image.height());
//    }

    engine::component::Material pbr_from_path (std::string_view path, size_t width, size_t height)
    {
        const auto pbr = resource::load(path, width, height);
        const auto gl_width = static_cast<GLsizei> (pbr.width);
        const auto gl_height = static_cast<GLsizei> (pbr.height);

        return
        {
            .tex_basecolor = load_texture(pbr.color_rgba, gl_width, gl_height, GL_RGBA),
            .tex_height    = load_texture(pbr.height_gray, gl_width, gl_height, GL_RED),
            .tex_mrao      = load_texture(pbr.mrao_rgb, gl_width, gl_height, GL_RGB),
            .tex_normal    = load_texture(pbr.normal_rgb, gl_width, gl_height, GL_RGB)
        };
    }
}

namespace asset::internal
{
    void init_materials ()
    {
        material::black_granite = pbr_from_path("./res/materials/gametextures/BlackGranite_2048x2048.pbr", 2048, 2048);
        material::broken_limestone_brick_path = pbr_from_path("./res/materials/gametextures/BrokenLimestoneBrickPath_2048x2048.pbr", 2048, 2048);
        material::chunky_wet_gravel_and_dirt = pbr_from_path("./res/materials/gametextures/ChunkyWetGravelAndDirt_2048x2048.pbr", 2048, 2048);
        material::dirty_hammered_copper = pbr_from_path("./res/materials/gametextures/DirtyHammeredCopper_2048x2048.pbr", 2048, 2048);
        material::pile_of_skulls = pbr_from_path("./res/materials/gametextures/PileOfSkulls_2048x2048.pbr", 2048, 2048);
        material::wool_woven_carpet_striped_burgundy = pbr_from_path("./res/materials/gametextures/WoolWovenCarpetStripedBurgundy_2048x2048.pbr", 2048, 2048);
    }
}
