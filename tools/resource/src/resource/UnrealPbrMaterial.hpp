#pragma once

#include <resource/PbrMaterial.hpp>

#include <QString>
#include <QImage>

#include <cstdlib>
#include <string_view>

namespace resource
{
    struct UnrealPbrMaterial
    {
    private:

        const QImage basecolor_image;
        const QImage emissive_image;
        const QImage height_image;
        const QImage mrao_image;
        const QImage normal_image;
        const QImage opacity_image;

    public:

        static constexpr size_t argb_bytes = 4;

        const size_t height;
        const size_t width;
        const size_t length;

        const unsigned char *basecolor_argb;
        const unsigned char *emissive_argb;
        const unsigned char *height_argb;
        const unsigned char *mrao_argb;
        const unsigned char *normal_argb;
        const unsigned char *opacity_argb;

    public:

        explicit UnrealPbrMaterial (std::string_view base_path)
                : basecolor_image(QImage{QString{base_path.data()} + QString{"_basecolor.png"}}.convertToFormat(QImage::Format_ARGB32))
                , emissive_image(QImage{QString{base_path.data()} + QString{"_emissive.png"}}.convertToFormat(QImage::Format_ARGB32))
                , height_image(QImage{QString{base_path.data()} + QString{"_height.png"}}.convertToFormat(QImage::Format_ARGB32))
                , mrao_image(QImage{QString{base_path.data()} + QString{"_mrao.png"}}.convertToFormat(QImage::Format_ARGB32))
                , normal_image(QImage{QString{base_path.data()} + QString{"_normal.png"}}.convertToFormat(QImage::Format_ARGB32))
                , opacity_image(QImage{QString{base_path.data()} + QString{"_opacity.png"}}.convertToFormat(QImage::Format_ARGB32))
                , height(static_cast<size_t> (basecolor_image.height()))
                , width(static_cast<size_t> (basecolor_image.width()))
                , length(height * height)
        {
            basecolor_argb = basecolor_image.bits();
            emissive_argb = emissive_image.bits();
            height_argb = height_image.bits();
            mrao_argb = mrao_image.bits();
            normal_argb = normal_image.bits();
            opacity_argb = opacity_image.bits();
        }
    };

    PbrMaterial fromUnreal (const UnrealPbrMaterial &src)
    {
        PbrMaterial dst{src.width, src.height};
        // notice that even we converted the image to ARGB32 the
        // QImage memory layout (B G R A and reversed lines) applies!

        {
            auto p = UnrealPbrMaterial::argb_bytes * (src.length - src.width);
            auto q = 0;
            for (size_t i = 0; i < src.height; ++i)
            {
                const auto end = p + (UnrealPbrMaterial::argb_bytes * src.width);
                while (p < end)
                {
                    dst.height_gray[q] = src.height_argb[p + 2]; // R
                    p += UnrealPbrMaterial::argb_bytes;
                    q += PbrMaterial::height_bytes;
                }
                p -= UnrealPbrMaterial::argb_bytes * (src.width + src.width);
            }
        }

        {
            auto p = UnrealPbrMaterial::argb_bytes * (src.length - src.width);
            auto q = 0;

            for (size_t i = 0; i < src.height; ++i)
            {
                const auto end = p + (UnrealPbrMaterial::argb_bytes * src.width);
                while (p < end)
                {
                    dst.color_rgba[q + 0] = src.basecolor_argb[p + 2]; // R
                    dst.color_rgba[q + 1] = src.basecolor_argb[p + 1]; // G
                    dst.color_rgba[q + 2] = src.basecolor_argb[p + 0]; // B
                    dst.color_rgba[q + 3] = src.opacity_argb[p + 1]; // R
                    p += UnrealPbrMaterial::argb_bytes;
                    q += PbrMaterial::color_bytes;
                }
                p -= UnrealPbrMaterial::argb_bytes * (src.width + src.width);
            }
        }

        {
            auto p = UnrealPbrMaterial::argb_bytes * (src.length - src.width);
            auto q = 0;
            for (size_t i = 0; i < src.height; ++i)
            {
                const auto end = p + (UnrealPbrMaterial::argb_bytes * src.width);
                while (p < end)
                {
                    dst.normal_rgb[q + 0] = src.normal_argb[p + 2]; // R
                    dst.normal_rgb[q + 1] = src.normal_argb[p + 1]; // G
                    dst.normal_rgb[q + 2] = src.normal_argb[p + 0]; // B
                    p += UnrealPbrMaterial::argb_bytes;
                    q += PbrMaterial::normal_bytes;
                }
                p -= UnrealPbrMaterial::argb_bytes * (src.width + src.width);
            }
        }

        {
            auto p = UnrealPbrMaterial::argb_bytes * (src.length - src.width);
            auto q = 0;
            for (size_t i = 0; i < src.height; ++i)
            {
                const auto end = p + (UnrealPbrMaterial::argb_bytes * src.width);
                while (p < end)
                {
                    dst.mrao_rgb[q + 0] = src.mrao_argb[p + 2]; // R
                    dst.mrao_rgb[q + 1] = src.mrao_argb[p + 1]; // G
                    dst.mrao_rgb[q + 2] = src.mrao_argb[p + 0]; // B
                    p += UnrealPbrMaterial::argb_bytes;
                    q += PbrMaterial::mrao_bytes;
                }
                p -= UnrealPbrMaterial::argb_bytes * (src.width + src.width);
            }
        }

        {
            auto p = UnrealPbrMaterial::argb_bytes * (src.length - src.width);
            auto q = 0;
            for (size_t i = 0; i < src.height; ++i)
            {
                const auto end = p + (UnrealPbrMaterial::argb_bytes * src.width);
                while (p < end)
                {
                    dst.emissive_gray[q] = src.emissive_argb[p + 2]; // R
                    p += UnrealPbrMaterial::argb_bytes;
                    q += PbrMaterial::emissive_bytes;
                }
                p -= UnrealPbrMaterial::argb_bytes * (src.width + src.width);
            }
        }

        return dst;
    }
}
