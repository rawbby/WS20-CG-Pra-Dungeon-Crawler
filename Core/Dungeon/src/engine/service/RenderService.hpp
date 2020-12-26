#pragma once

#include <engine/component/DynamicCollisionComponent.hpp>
#include <engine/component/StaticCollisionComponent.hpp>
#include <engine/component/PositionComponent.hpp>

#include <entt/entt.hpp>

namespace engine::service
{
    class RenderService
    {
    private:

        /**
         * Collection of all entities that provide only
         * a GlRenderComponent for rendering.
         */
        std::vector <entt::entity> m_renderer_entities{};

        /**
         * Collection of all entities that provide
         * a GlMaterialComponent for rendering.
         * GlRenderComponent needs also to be provided.
         */
        std::vector <entt::entity> m_material_entities{};

        /**
         * Collection of all entities that provide
         * a GlBlendMaterialComponent for rendering.
         * GlRenderComponent needs also to be provided.
         */
        std::vector <entt::entity> m_blend_material_entities{};

    public:

        void update (entt::registry &reg, float delta);
    };
}
