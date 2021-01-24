#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

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

    engine::component::Material pbr_from_path (std::string_view path, size_t width, size_t height, float height_mult)
    {
        const auto pbr = resource::load(path, width, height);
        const auto gl_width = static_cast<GLsizei> (pbr.width);
        const auto gl_height = static_cast<GLsizei> (pbr.height);

        return {.tex_basecolor = load_texture(pbr.color_rgba, gl_width, gl_height, GL_RGBA), .tex_height    = load_texture(pbr.height_gray, gl_width, gl_height, GL_RED), .tex_mrao      = load_texture(pbr.mrao_rgb, gl_width, gl_height, GL_RGB), .tex_normal    = load_texture(pbr.normal_rgb, gl_width, gl_height, GL_RGB), .tex_height_mult = height_mult};
    }
}

namespace asset::internal
{
    void init_materials ()
    {
        material::black_granite = pbr_from_path("./res/materials/gametextures/BlackGranite_2048x2048.pbr", 2048, 2048, 0.0f);
        material::black_ostrich_hide_wrinkles_2 = pbr_from_path("./res/materials/gametextures/BlackOstrichHideWrinkles2_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::broken_limestone_brick_path = pbr_from_path("./res/materials/gametextures/BrokenLimestoneBrickPath_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::chunky_wet_gravel_and_dirt = pbr_from_path("./res/materials/gametextures/ChunkyWetGravelAndDirt_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::clay_01 = pbr_from_path("./res/materials/gametextures/Clay01_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::cracked_red_ceramic_roof = pbr_from_path("./res/materials/gametextures/CrackedRedCeramicRoof_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::dirty_hammered_copper = pbr_from_path("./res/materials/gametextures/DirtyHammeredCopper_2048x2048.pbr", 2048, 2048, 0.02f);
        material::pile_of_skulls = pbr_from_path("./res/materials/gametextures/PileOfSkulls_2048x2048.pbr", 2048, 2048, 0.046875f);
        material::white_wool_cloth = pbr_from_path("./res/materials/gametextures/WhiteWoolCloth_2048x2048.pbr", 2048, 2048, 0.02f);
        material::wool_woven_carpet_striped_burgundy = pbr_from_path("./res/materials/gametextures/WoolWovenCarpetStripedBurgundy_2048x2048.pbr", 2048, 2048, 0.02f);
    }
}

