#pragma once

// expose interface

#include <asset/Drawable.hpp>
#include <asset/Material.hpp>
#include <asset/Program.hpp>
#include <asset/Vao.hpp>

namespace asset
{
    void init_assets ()
    {
        internal::init_programs();
        internal::init_materials();
        internal::init_vaos();

        // NOTICE: drawables needs to be initialized last!
        internal::init_drawables();
    }
}
