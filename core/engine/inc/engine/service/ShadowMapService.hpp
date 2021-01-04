#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

namespace engine::service
{
    class ShadowMap
    {
    public:

        void init ();

        void update (entt::registry &reg);
    };
}
