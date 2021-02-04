#pragma once

#include <engine/component/PositionComponent.hpp>

#include "engine/service/CollisionService.hpp"
#include "engine/service/RenderService.hpp"
#include "engine/service/ShadowMapService.hpp"
#include <engine/Entity.hpp>

#include <engine/service/AnimatorService.hpp>

#include <entt/entt.hpp>

namespace engine
{
    class Game
    {
    protected:

        entt::registry m_registry{};

    protected:

        service::Animator m_animator;
        service::Collision m_collision;
        service::ShadowMap m_shadow_map;
        service::Render m_render;

    public:

        Entity add_entity (component::PositionComponent position = {})
        {
            Entity entity = m_registry.create();
            m_registry.emplace<component::PositionComponent>(entity, position);
            return entity;
        }

        template <typename Component, typename ...Args>
        Component &add_component (Entity entity, Args &&... args)
        {
            return m_registry.emplace<Component>(entity, std::forward<Args>(args)...);
        }

        template <typename Component>
        Component &get_component (Entity entity)
        {
            return m_registry.get<Component>(entity);
        }

        template <typename Component, typename ...Args>
        bool has_component (Entity entity, Args &&... args)
        {
            return m_registry.has<Component>(entity);
        }
    };
}
