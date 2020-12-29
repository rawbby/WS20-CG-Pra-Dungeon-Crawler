#pragma once

namespace engine::component
{
    /**
     * Axis aligned bounding box.
     * Used for all static collision components.
     *
     * Entities with this component also
     * need to have the PositionComponent
     * to be used with the CollisionService.
     */
    struct StaticCollisionComponent
    {
        float half_width = 0.0f;
        float half_height = 0.0f;
    };
}
