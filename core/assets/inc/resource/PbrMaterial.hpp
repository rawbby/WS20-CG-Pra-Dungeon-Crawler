#pragma once

#include <cstdlib>
#include <memory>
#include <string_view>

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <spdlog/spdlog.h>

namespace resource
{
    struct PbrMaterial
    {
    public:

        static constexpr size_t height_bytes = 1; // Grayscale8
        static constexpr size_t color_bytes = 4; // RGBA32
        static constexpr size_t normal_bytes = 3; // RGB888
        static constexpr size_t mrao_bytes = 3; // RGBA32
        static constexpr size_t emissive_bytes = 1; // Grayscale8

        const size_t width;
        const size_t height;
        const size_t length;
        const size_t size;

    private:

        std::unique_ptr<unsigned char[]> data_ptr;

    public:

        unsigned char *data;
        unsigned char *height_gray;
        unsigned char *color_rgba;
        unsigned char *normal_rgb;
        unsigned char *mrao_rgb;
        unsigned char *emissive_gray;

    public:

        explicit PbrMaterial (const size_t width, const size_t height)
                : width(width)
                , height(height)
                , length(width * height)
                , size(length * (height_bytes + color_bytes + normal_bytes + mrao_bytes + emissive_bytes))
                , data_ptr(std::make_unique<unsigned char[]>(size))
                , data(data_ptr.get())
        {
            const size_t height_offset = 0;
            const size_t color_offset = height_offset + length * height_bytes;
            const size_t normal_offset = color_offset + length * color_bytes;
            const size_t mrao_offset = normal_offset + length * normal_bytes;
            const size_t emissive_offset = mrao_offset + length * mrao_bytes;

            height_gray = &(data[height_offset]);
            color_rgba = &(data[color_offset]);
            normal_rgb = &(data[normal_offset]);
            mrao_rgb = &(data[mrao_offset]);
            emissive_gray = &(data[emissive_offset]);
        }
    };

    PbrMaterial load (std::string_view path, size_t width, size_t height)
    {
        auto pbr_file = QFile{path.data()};
        if (!pbr_file.open(QIODevice::ReadOnly))
        {
            spdlog::error(R"(Cannot open file for reading! (FILE: "{}", LINE: "{}" PATH: "{}" STATUS: "{}"))", __FILE__, __LINE__, path, qPrintable(pbr_file.errorString()));
            return PbrMaterial{0, 0};
        }

        auto dst = PbrMaterial{width, height};
        pbr_file.read(reinterpret_cast<char *> (dst.data), dst.size);

        return dst;
    }

    PbrMaterial load (std::string_view path)
    {
        auto pbr_name = QString{path.data()};

        auto begin = pbr_name.lastIndexOf('_');
        auto split = pbr_name.lastIndexOf('x');
        auto end = pbr_name.lastIndexOf('.');

        auto width = pbr_name.mid(begin + 1, split - begin - 1).toULongLong();
        auto height = pbr_name.mid(split + 1, end - split - 1).toULongLong();

        return load(path, width, height);
    }
}
