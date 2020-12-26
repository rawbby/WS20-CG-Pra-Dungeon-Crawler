#pragma once

#include <engine/service/CollisionService.hpp>
#include <engine/service/RenderService.hpp>

#include <entt/entt.hpp>

namespace engine
{
    class Game
    {
    private:

        service::CollisionService m_collision_service{};
        service::RenderService m_render_service{};

        entt::registry m_registry{};

    public:

        void update(float delta);
    };
}
