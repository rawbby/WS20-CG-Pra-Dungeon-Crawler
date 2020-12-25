#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/common.hpp>

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

int main (int argc, char **argv)
{
    initializeSpdlog();
    initializeQtOpenGL();

    QApplication app{argc, argv};

    MainWindow window{};
    window.show();

    return QApplication::exec();
}
