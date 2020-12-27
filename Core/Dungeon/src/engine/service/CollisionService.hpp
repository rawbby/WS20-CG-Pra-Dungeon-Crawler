#pragma once

#include <engine/service/CollisionService.hpp>

#include <engine/component/DynamicCollisionComponent.hpp>
#include <engine/component/StaticCollisionComponent.hpp>
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
