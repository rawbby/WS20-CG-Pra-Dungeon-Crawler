#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/common.hpp>

#include <spdlog/spdlog.h>

#include <QApplication>
#include <MainWindow.hpp>

int main (int argc, char **argv)
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Hello World!");

    QApplication app{argc, argv};

    MainWindow window{};
    window.show();

    return QApplication::exec();
}
