#pragma once

#include <glm/glm.hpp>

namespace engine::component
{
    /**
     * Needed input for OpenGl to render a object.
     */
    struct GlRenderComponent
    {
        GLuint program = GL_NONE;
        GLuint vao = GL_NONE;
        GLuint vao_lr = GL_NONE;
        GLsizei count = 0u;
        GLsizei count_lr = 0u;
        glm::mat4 model_view_matrix = glm::mat4{1.0f};
    };
}
