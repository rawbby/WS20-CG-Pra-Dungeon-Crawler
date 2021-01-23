#pragma once

#include "CollisionService.hpp"

#include <engine/component/DynamicCollisionCircle.hpp>
#include <engine/component/StaticCollisionLine.hpp>
#include <engine/component/PositionComponent.hpp>

#include <glm/ext/quaternion_common.hpp>

#include <entt/entt.hpp>

namespace engine::service
{
    class Collision
    {
    public:

        void init ();

        void update (entt::registry &reg, float delta);
    };
}
