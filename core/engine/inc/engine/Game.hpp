#pragma once

#include <engine/component/PositionComponent.hpp>

#include <engine/service/AnimationService.hpp>
#include <engine/service/CollisionService.hpp>
#include <engine/service/RenderService.hpp>
#include <engine/Entity.hpp>

#include <entt/entt.hpp>

namespace engine
{
    class Game
    {
    protected:

        entt::registry m_registry{};

    protected:

        service::Collision m_collision{};
        service::AnimationService m_animation;
        service::Render m_render;

    public:

        void init ()
        {
            m_render.init();
        }

        void update (glm::mat4 projection_matrix, glm::mat4 camera_matrix, glm::vec3 camera_position, float delta)
        {
            m_collision.update(m_registry, delta);
            m_animation.update(m_registry, delta);
            m_render.update(m_registry, projection_matrix, camera_matrix, camera_position);
        }

    public:

        inline Entity create_entity (component::PositionComponent position = {})
        {
            Entity entity{m_registry.create()};
            add_component<component::PositionComponent>(entity, position);
            return entity;
        }

        template <typename Component, typename ...Args>
        inline Component &add_component (Entity entity, Args &&... args)
        {
            return m_registry.emplace<Component>(entity.m_id, std::forward<Args>(args)...);
        }

        template <typename Component>
        inline Component &get_component (Entity entity)
        {
            return m_registry.get<Component>(entity.m_id);
        }

        template <typename Component>
        inline bool has_component (Entity entity)
        {
            return m_registry.has<Component>(entity.m_id);
        }
    };
}
