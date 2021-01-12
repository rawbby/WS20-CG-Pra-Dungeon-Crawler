#pragma once

#include <entt/entt.hpp>

namespace engine
{
    class Game;

    class Service;

    struct Entity
    {
        friend Game;
        friend Service;

    protected:

        entt::entity m_id = entt::null;

    public:

        constexpr Entity () noexcept = default;
        constexpr Entity (Entity &&) noexcept = default;
        constexpr Entity (const Entity &) noexcept = default;

        constexpr Entity &operator= (Entity &&) noexcept = default;
        constexpr Entity &operator= (const Entity &) noexcept = default;

    protected:

        explicit constexpr Entity (entt::entity id) noexcept
                : m_id(id)
        {
        }

        constexpr Entity &operator= (entt::entity id) noexcept
        {
            m_id = id;
            return *this;
        }

        constexpr explicit operator entt::entity () const noexcept
        {
            return m_id;
        }

    protected:

        template <typename Component, typename ...Args>
        inline Component &add_component (entt::registry &registry, Args &&... args) const
        {
            return registry.emplace<Component>(m_id, std::forward<Args>(args)...);
        }

        template <typename Component>
        inline Component &get_component (entt::registry &registry) const
        {
            return registry.get<Component>(m_id);
        }

        template <typename Component>
        inline bool has_component (entt::registry &registry) const
        {
            return registry.has<Component>(m_id);
        }
    };
}
