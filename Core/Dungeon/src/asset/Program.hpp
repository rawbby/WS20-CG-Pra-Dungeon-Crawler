#pragma once

namespace asset
{
    namespace internal
    {
        void init_programs ();
    }

    namespace program
    {
        [[maybe_unused]] inline GLuint trivial{};
        [[maybe_unused]] inline GLuint material{};
        [[maybe_unused]] inline GLuint pbr{};
    }
}
