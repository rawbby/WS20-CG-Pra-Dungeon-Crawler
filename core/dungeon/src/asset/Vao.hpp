#pragma once

namespace asset::internal
{
    void init_vaos ();

    namespace vao
    {
        [[maybe_unused]] inline GLuint plane = GL_NONE;
        [[maybe_unused]] inline GLsizei plane_count = 0;

        [[maybe_unused]] inline GLuint sphere = GL_NONE;
        [[maybe_unused]] inline GLsizei sphere_count = 0;
    }
}
