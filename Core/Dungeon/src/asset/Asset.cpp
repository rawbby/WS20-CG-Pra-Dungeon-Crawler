#include <GL/glew.h>
#include <GL/GL.h>

#include <algorithm>

#include <asset/Asset.hpp>
#include <asset/Util.hpp>

#include <common/FileUtil.hpp>
#include <geometries/Geometries.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <QOpenGLTexture>

// TODO get rid od Qt in this file!
#include <QImage>
#include <QOpenGLTexture>

namespace asset::vao
{
    namespace mvm
    {
        glm::mat4 plane_bottom{};
        glm::mat4 plane_back{};
        glm::mat4 plane_right{};
        glm::mat4 plane_front{};
        glm::mat4 plane_left{};
        glm::mat4 plane_top{};
    }

    [[maybe_unused]] GLuint  plane       = GL_NONE;
    [[maybe_unused]] GLsizei plane_count = 0;
}

namespace
{
    GLuint vertex_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return asset::util::compile_vertex_shader(common::load_text(path));
    }

    GLuint fragment_shader_from_path (std::string_view path) noexcept // check if noexcept is true
    {
        return asset::util::compile_fragment_shader(common::load_text(path));
    }

    GLuint texture_from_path (std::string_view path) noexcept // check if noexcept is true
    {   // TODO workaround used! copied QGLWidget's convertToGlFormat function from Qt5 wich is not supported anymore.

        using namespace asset;

        auto qt_image = QImage(QString(path.data()));
        qt_image.convertTo(QImage::Format_ARGB32);

        QImage gl_image(qt_image.size(), QImage::Format_ARGB32);

        const auto width  = qt_image.width();
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

        return util::load_texture(gl_image.bits(), gl_image.width(), gl_image.height());
    }

    void load_programs ()
    {
        using namespace asset;

        const auto material_vertex_shader = vertex_shader_from_path(":/glsl/Material.vs.glsl");
        const auto trivial_vertex_shader  = vertex_shader_from_path(":/glsl/Trivial.vs.glsl");

        const auto material_fragment_shader    = fragment_shader_from_path(":/glsl/Material.fs.glsl");
        const auto trivial_red_fragment_shader = fragment_shader_from_path(":/glsl/TrivialRed.fs.glsl");

        program::material = asset::util::compile_program(material_vertex_shader, material_fragment_shader);
        program::trivial  = asset::util::compile_program(trivial_vertex_shader, trivial_red_fragment_shader);

        glDeleteShader(material_vertex_shader);
        glDeleteShader(trivial_vertex_shader);

        glDeleteShader(material_fragment_shader);
        glDeleteShader(trivial_red_fragment_shader);
    }

    void load_textures ()
    {
        using namespace asset;

        material::pile_of_skulls_basecolor = texture_from_path(":/materials/gametextures/PileOfSkulls_basecolor.png");
        material::pile_of_skulls_height    = texture_from_path(":/materials/gametextures/PileOfSkulls_height.png");
        material::pile_of_skulls_mrao      = texture_from_path(":/materials/gametextures/PileOfSkulls_mrao.png");
        material::pile_of_skulls_normal    = texture_from_path(":/materials/gametextures/PileOfSkulls_normal.png");

        material::black_granite_basecolor = texture_from_path(":/materials/gametextures/BlackGranite_basecolor.png");
        material::black_granite_height    = texture_from_path(":/materials/gametextures/BlackGranite_height.png");
        material::black_granite_mrao      = texture_from_path(":/materials/gametextures/BlackGranite_mrao.png");
        material::black_granite_normal    = texture_from_path(":/materials/gametextures/BlackGranite_normal.png");

        material::broken_limestone_brick_path_basecolor = texture_from_path(":/materials/gametextures/BrokenLimestoneBrickPath_basecolor.png");
        material::broken_limestone_brick_path_height    = texture_from_path(":/materials/gametextures/BrokenLimestoneBrickPath_height.png");
        material::broken_limestone_brick_path_mrao      = texture_from_path(":/materials/gametextures/BrokenLimestoneBrickPath_mrao.png");
        material::broken_limestone_brick_path_normal    = texture_from_path(":/materials/gametextures/BrokenLimestoneBrickPath_normal.png");
    }

    void load_vaos ()
    {
        using namespace asset;

        constexpr size_t DIVISIONS        = 1024;
        auto             plane_points     = geometries::generate_plane_bottom_points<DIVISIONS>();
        auto             plane_indices    = geometries::generate_plane_bottom_indices<DIVISIONS>();
        auto             plane_normals    = geometries::generate_plane_bottom_normals<DIVISIONS>();
        auto             plane_tex_coords = geometries::generate_plane_bottom_tex_coords<DIVISIONS>(); // TODO check why not const

        vao::plane       = util::generate_vao(plane_points, plane_indices, plane_normals, plane_tex_coords);
        vao::plane_count = plane_indices.size();

        vao::mvm::plane_bottom = glm::identity<glm::mat4>();
        vao::mvm::plane_back   = glm::rotate(vao::mvm::plane_bottom, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        vao::mvm::plane_right  = glm::rotate(vao::mvm::plane_back, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        vao::mvm::plane_front  = glm::rotate(vao::mvm::plane_back, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        vao::mvm::plane_left   = glm::rotate(vao::mvm::plane_back, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        vao::mvm::plane_top    = glm::translate(vao::mvm::plane_bottom, glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

namespace asset
{

    namespace drawable
    {   //@formatter:off
        MaterialDrawable create_floor ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_bottom,
                material::pile_of_skulls_basecolor,
                material::pile_of_skulls_height,
                material::pile_of_skulls_mrao,
                material::pile_of_skulls_normal
            };
        }

        MaterialDrawable create_wall_back ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_back,
                material::broken_limestone_brick_path_basecolor,
                material::broken_limestone_brick_path_height,
                material::broken_limestone_brick_path_mrao,
                material::broken_limestone_brick_path_normal
            };
        }

        MaterialDrawable create_wall_right ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_right,
                material::broken_limestone_brick_path_basecolor,
                material::broken_limestone_brick_path_height,
                material::broken_limestone_brick_path_mrao,
                material::broken_limestone_brick_path_normal
            };
        }

        MaterialDrawable create_wall_front ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_front,
                material::broken_limestone_brick_path_basecolor,
                material::broken_limestone_brick_path_height,
                material::broken_limestone_brick_path_mrao,
                material::broken_limestone_brick_path_normal
            };
        }

        MaterialDrawable create_wall_left ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_left,
                material::broken_limestone_brick_path_basecolor,
                material::broken_limestone_brick_path_height,
                material::broken_limestone_brick_path_mrao,
                material::broken_limestone_brick_path_normal
            };
        }

        MaterialDrawable create_wall_top ()
        {
            return
            {
                program::material,
                vao::plane,
                vao::plane_count,
                vao::mvm::plane_top,
                material::broken_limestone_brick_path_basecolor,
                material::broken_limestone_brick_path_height,
                material::broken_limestone_brick_path_mrao,
                material::broken_limestone_brick_path_normal
            };
        }
    }   //@formatter:on

    void load_assets ()
    {
        load_programs();
        load_textures();
        load_vaos();
    }
}
