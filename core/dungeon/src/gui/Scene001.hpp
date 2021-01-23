#include <engine/Entity.hpp>
#include <engine/Game.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <engine/component/DynamicCollisionCircle.hpp>
#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/GlPointLightComponent.hpp>
#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/PositionComponent.hpp>
#include <engine/component/StaticCollisionLine.hpp>

#include <asset/Asset.hpp>

namespace scene001
{
    using namespace engine;
    using namespace component;
    using namespace asset;

    void create_scene (Game &game, Entity &player)
    {
        player = game.add_entity();
        game.add_component<GlMaterialComponent>(player, program::pbr, vao::sphere, vao::sphere_lr, vao::sphere_count, vao::sphere_lr_count, glm::scale(glm::mat4{1.0f}, glm::vec3{0.1f}), material::dirty_hammered_copper);
        game.add_component<DynamicCollisionCircle>(player, DynamicCollisionCircle{glm::vec2{}, 0.2f});
        game.add_component<GlPointLightComponent>(player, glm::vec3{0.4f, 0.4f, 0.3f}, 0.0f, asset::program::shadow);

        // create main light source
        game.add_component<GlPointLightComponent>(game.add_entity({1.0f, 1.0f}), glm::vec3{0.8f, 0.3f, 0.3f}, 1.0f, asset::program::shadow);
        game.add_component<GlPointLightComponent>(game.add_entity({-1.0f, -1.0f}), glm::vec3{0.1f, 0.5f, 0.1f}, -0.125f, asset::program::shadow);

        // create the wall collision
        game.add_component<StaticCollisionLine>(game.add_entity(), glm::vec2{-1.5f, -1.5f}, glm::vec2{3.0f, 0.0f});
        game.add_component<StaticCollisionLine>(game.add_entity(), glm::vec2{1.5f, -1.5f}, glm::vec2{0.0f, 3.0f});
        game.add_component<StaticCollisionLine>(game.add_entity(), glm::vec2{1.5f, 1.5f}, glm::vec2{-3.0f, 0.0f});
        game.add_component<StaticCollisionLine>(game.add_entity(), glm::vec2{-1.5f, 1.5f}, glm::vec2{0.0f, -3.0f});

        // create visual floor
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, -1.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 0.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 1.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({0.0f, -1.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({0.0f, 0.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({0.0f, 1.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, -1.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, 0.0f}), asset::material::create_floor());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, 1.0f}), asset::material::create_floor());

        // create visual wall back
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, -1.0f}), asset::material::create_wall_back());
        game.add_component<GlMaterialComponent>(game.add_entity({0.0f, -1.0f}), asset::material::create_wall_back());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, -1.0f}), asset::material::create_wall_back());

        // create visual wall right
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, -1.0f}), asset::material::create_wall_right());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, 0.0f}), asset::material::create_wall_right());
        game.add_component<GlMaterialComponent>(game.add_entity({1.0, 1.0f}), asset::material::create_wall_right());

        // create visual wall front
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, 1.0f}), asset::material::create_wall_front());
        game.add_component<GlMaterialComponent>(game.add_entity({0.0f, 1.0f}), asset::material::create_wall_front());
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 1.0f}), asset::material::create_wall_front());

        // create visual wall left
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 1.0f}), asset::material::create_wall_left());
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 0.0f}), asset::material::create_wall_left());
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, -1.0f}), asset::material::create_wall_left());

        // create granite orb
        game.add_component<GlMaterialComponent>(game.add_entity({-1.0f, 0.0f}), program::pbr, vao::sphere, vao::sphere_lr, vao::sphere_count, vao::sphere_lr_count, glm::scale(glm::mat4{1.0f}, glm::vec3{0.25f}), material::black_granite);
        game.add_component<GlMaterialComponent>(game.add_entity({1.0f, 1.0f}), program::pbr, vao::sphere, vao::sphere_lr, vao::sphere_count, vao::sphere_lr_count, glm::scale(glm::mat4{1.0f}, glm::vec3{0.125f}), material::black_granite);
    }
}
