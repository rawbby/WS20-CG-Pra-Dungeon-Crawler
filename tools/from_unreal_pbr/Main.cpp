#pragma once

#include <spdlog/spdlog.h>
#include <string>

#include <QString>
#include <QIODevice>
#include <QFile>

#include <resource/PbrMaterial.hpp>
#include <resource/UnrealPbrMaterial.hpp>

int main (int argc, char *args[])
{
    using namespace resource;

    spdlog::set_level(spdlog::level::debug);

    if (argc < 3)
    {
        spdlog::error("Insufficient arguments!");
        return EXIT_FAILURE;
    }

    const auto vendor = std::string{args[1]};

    for (int i = 2; i < argc; ++i)
    {
        const auto base_path = vendor + '/' + std::string{args[i]};

        const auto src = UnrealPbrMaterial{base_path};
        const auto dst = fromUnreal(src);

        auto width = QString::number(dst.width);
        auto height = QString::number(dst.height);

        auto pbr_name = QString{base_path.data()} + QString{"_"} + width + QString{"x"} + height + QString{".pbr"};
        auto pbr_file = QFile{pbr_name};
        if (!pbr_file.open(QIODevice::WriteOnly))
        {
            spdlog::error("Cannot open file for writing: {}!", qPrintable(pbr_file.errorString()));
            return EXIT_FAILURE;
        }

        pbr_file.write(reinterpret_cast<const char *>(dst.data), dst.size);
        auto test = load(pbr_name.toStdString(), dst.width, dst.height);
    }

    return EXIT_SUCCESS;
}
