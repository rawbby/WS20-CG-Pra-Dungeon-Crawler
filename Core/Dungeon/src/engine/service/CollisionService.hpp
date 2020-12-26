#pragma once

#include <engine/component/DynamicCollisionComponent.hpp>
#include <engine/component/StaticCollisionComponent.hpp>
#include <engine/component/PositionComponent.hpp>

#include <entt/entt.hpp>

namespace engine::service
{
    /**
     * model view matrix used by RendererService
     * to translate vao positions.
     *
     * In combination with the PositionComponent
     * the real position is determent.
     */
    class CollisionService
    {
    private:

        /**
         * Collection of all entities that are interpreted as
         * static colliders.
         * Static colliders provide a StaticCollisionComponent
         * and PositionComponent.
         */
        std::vector <entt::entity> m_static_collision_entities{};

        /**
         * Collection of all entities that are interpreted as
         * dynamic colliders.
         * Dynamic colliders provide a DynamicCollisionComponent
         * and PositionComponent.
         */
        std::vector <entt::entity> m_dynamic_collision_entities{};

    public:

        void update (entt::registry &reg, float delta);
    };
}
