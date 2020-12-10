#include <GL/glew.h>
#include <GL/GL.h>

#include <common/FileUtil.hpp>
#include <shader/Util.hpp>

#include <spdlog/spdlog.h>

#include <QFile>
#include <QTextStream>
#include <QOpenGLWidget>

namespace common
{
    std::string load_text (std::string_view path)
    {
        QFile file{path.data()};
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            spdlog::error("QFILE CAN NOT BE OPENED! path: ", path);
            return "";
        }

        auto result = QTextStream{&file}.readAll().toStdString();
        file.close();

        return result;
    }

    QImage load_image (std::string_view path)
    {
        return QImage{path.data()};
    }

    QImage load_image_argb32 (std::string_view path)
    {
        auto image = QImage{path.data()};
        image.convertTo(QImage::Format_ARGB32);

        return image;
    }
}
