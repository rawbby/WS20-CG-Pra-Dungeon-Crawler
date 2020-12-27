#pragma once

#include <engine/component/PositionComponent.hpp>

#include <engine/service/CollisionService.hpp>
#include <engine/service/RenderService.hpp>
#include <engine/Entity.hpp>

#include <entt/entt.hpp>

namespace engine
{
    class Game
    {
    private:

        entt::registry m_registry{};

    private:

        service::Collision m_collision;
        service::Render m_render;

    public:

        void init ()
        {
            m_collision.init();
            m_render.init();
        }

        void update (glm::mat4 projection_matrix, glm::mat4 camera_matrix, float delta)
        {
            m_collision.update(m_registry, delta);
            m_render.update(m_registry, projection_matrix, camera_matrix);
        }

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
