#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

namespace engine::service
{
    class Render
    {
    public:

        void init ();

        void update (entt::registry &reg, glm::mat4 projection_matrix, glm::mat4 camera_matrix);
    };
}
