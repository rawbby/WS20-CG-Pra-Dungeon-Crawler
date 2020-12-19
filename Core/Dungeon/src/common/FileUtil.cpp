#include <GL/glew.h>
#include <GL/GL.h>

#include <common/FileUtil.hpp>
#include <asset/Util.hpp>

#include <spdlog/spdlog.h>

#include <QFile>
#include <QTextStream>

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
}
