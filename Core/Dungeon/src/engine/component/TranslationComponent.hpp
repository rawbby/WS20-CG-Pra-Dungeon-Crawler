#pragma once

#include <glm/mat4x4.hpp>

namespace engine::component
{
    /**
     * model view matrix used by RendererService
     * to translate vao positions.
     *
     * In combination with the PositionComponent
     * the real position is determent.
     */
    struct TranslationComponent
    {
        glm::mat4 model_view_matrix{};
    };
}
