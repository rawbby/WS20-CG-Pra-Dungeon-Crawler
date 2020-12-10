#pragma once

#include <string_view>
#include <QImage>

namespace common
{
    std::string load_text (std::string_view path);
    QImage load_image (std::string_view path);
    QImage load_image_argb32 (std::string_view path);
}
