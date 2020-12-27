#pragma once

#include <engine/service/RenderService.hpp>

#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/GlBlendMaterialComponent.hpp>

#include <engine/component/PositionComponent.hpp>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entt/entt.hpp>

namespace engine::service
{
    class Render
    {
    public:

        void init ();

        void update (entt::registry &reg, glm::mat4 projection_matrix, glm::mat4 camera_matrix);
    };
}
