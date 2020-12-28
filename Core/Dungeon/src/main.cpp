#include <GL/glew.h>
#include <GL/GL.h>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include <QApplication>
#include <QSurfaceFormat>
#include <gui/MainWindow.hpp>

namespace
{
    void initializeSpdlog ()
    {
        spdlog::set_level(spdlog::level::debug);
    }

    void initializeQtOpenGL ()
    {
        auto format = QSurfaceFormat::defaultFormat();
        format.setMajorVersion(4);
        format.setMinorVersion(5);
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
        format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        QSurfaceFormat::setDefaultFormat(format);
    }
}

#include <geometries/Sphere.hpp>

int main (int argc, char **argv)
{
    initializeSpdlog();
    initializeQtOpenGL();

    // const auto points = geometries::generate_sphere_points(4, 3);
    // for (const auto point : points)
    // {
    //     spdlog::debug("({}, {}, {})", point.x, point.y, point.z);
    // }

    const auto indices = geometries::generate_sphere_indices(3, 5);

    QApplication app{argc, argv};

    MainWindow window{};
    window.show();

    return QApplication::exec();
}
