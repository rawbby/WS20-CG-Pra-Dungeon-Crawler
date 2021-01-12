#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

#include <engine/component/AnimatedModelComponent.hpp>

namespace engine::service
{
    class AnimationService
    {
    public:

        void update (entt::registry &reg, float delta)
        {
            using namespace component;

            {
                auto render_group = reg.group<JointAnimatorComponent>(entt::get<PositionComponent>);

                for (const auto entity: render_group)
                {
                    auto[position, data] = render_group.get<PositionComponent, JointAnimatorComponent>(entity);
                    data.update(delta);
                }
            }
        }
    };
}
