#include <GL/glew.h>
#include <GL/GL.h>

#include <shader/Util.hpp>
#include <spdlog/spdlog.h>

namespace shader
{
    bool check_error ()
    {
        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error("OPENGL ERROR! status: ", status);
            return false;
        }
        return true;
    }

    bool check_fbo_error ()
    {
        const auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (GL_FRAMEBUFFER_COMPLETE != status)
        {
            spdlog::error("OPENGL UNCOMPLETE FRAMEBUFFER! status: ", status);
            return false;
        }
        return true;
    }
}
