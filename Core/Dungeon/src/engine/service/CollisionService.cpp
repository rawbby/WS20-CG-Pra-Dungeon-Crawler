#include <engine/service/CollisionService.hpp>

#include <spdlog/spdlog.h>

namespace engine::service
{
    void Collision::init ()
    {
    }

    void Collision::update (entt::registry &reg, float delta)
    {
        using namespace component;

        auto static_group = reg.group<StaticCollisionComponent>(entt::get<PositionComponent>);
        auto dynamic_group = reg.group<DynamicCollisionComponent>(entt::get<PositionComponent>);

        const auto dynamic_size = dynamic_group.size();
        for (size_t i = 0; i < dynamic_size; ++i)
        {
            auto[dynamic_i, position_i] = dynamic_group.get<DynamicCollisionComponent, PositionComponent>(dynamic_group[i]);

            for (size_t j = 0; j < i; ++j)
            {
                auto[dynamic_j, position_j] = dynamic_group.get<DynamicCollisionComponent, PositionComponent>(dynamic_group[j]);

                const auto min_distance = dynamic_i.radius + dynamic_j.radius;
                const auto distance = glm::length((position_i + dynamic_i.velocity) - (position_j + dynamic_j.velocity));

                if (distance < min_distance)
                {
                    // TODO implement better collision handling
                    dynamic_i.velocity = {};
                    dynamic_j.velocity = {};
                }
            }
        }

        for (const auto entity_i: dynamic_group)
        {
            auto[dynamic_i, position_i] = dynamic_group.get<DynamicCollisionComponent, PositionComponent>(entity_i);

            for (const auto entity_j: static_group)
            {
                auto[static_j, position_j] = static_group.get<StaticCollisionComponent, PositionComponent>(entity_j);

                const auto min_distance = dynamic_i.radius + glm::max(static_j.half_width, static_j.half_height);
                const auto distance = glm::length((position_i + dynamic_i.velocity) - position_j);

                // TODO implement better collision detection dynamic/static
                // check out https://yal.cc/rectangle-circle-intersection-test
                if (distance < min_distance)
                {
                    // TODO implement better collision handling
                    dynamic_i.velocity = {};
                }
            }

            position_i += dynamic_i.velocity;
        }
    }
}
