#pragma once

#include "CollisionService.hpp"

#include <engine/component/DynamicCollisionCircle.hpp>
#include <engine/component/StaticCollisionLine.hpp>
#include <engine/component/PositionComponent.hpp>

#include <model/Types.hpp>
#include <model/Skin.hpp>
#include <model/SkinnedMesh.hpp>
#include <model/SkinAnimation.hpp>
#include <model/SkinTransitionAnimator.hpp>

#include <glm/ext/quaternion_common.hpp>

#include <entt/entt.hpp>

namespace engine::service
{
    class Animator
    {
    public:

        void update (entt::registry &reg, float delta)
        {
            auto ator_entities = reg.view<model::SkinTransitionAnimator>();

            for (const auto ator_entity: ator_entities)
            {
                auto &ator = reg.get<model::SkinTransitionAnimator>(ator_entity);
                model::update_transition_animation(ator, delta);
            }
        }
    };
}
