#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

#include <glm/gtx/transform.hpp>

#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/AnimatedModelComponent.hpp>

namespace
{
    engine::component::GlMaterialComponent create_plane (engine::component::Material material, glm::mat4 mvm)
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::pbr, vao::plane, vao::plane_count, mvm, material};
    }
}

namespace asset::material
{
    engine::component::GlMaterialComponent create_floor ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        return create_plane(asset::material::dirty_hammered_copper, mvm);
    }

    engine::component::GlMaterialComponent create_wall_back ()
    {
        auto mvm = glm::identity<glm::mat4>();
        return create_plane(asset::material::black_granite, mvm);
    }

    engine::component::GlMaterialComponent create_wall_right ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return create_plane(asset::material::broken_limestone_brick_path, mvm);
    }

    engine::component::GlMaterialComponent create_wall_front ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::rotate(mvm, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return create_plane(asset::material::broken_limestone_brick_path, mvm);
    }

    engine::component::GlMaterialComponent create_wall_left ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::rotate(mvm, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        return create_plane(asset::material::chunky_wet_gravel_and_dirt, mvm);
    }

    engine::component::GlMaterialComponent create_top ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::translate(mvm, glm::vec3(0.0f, 1.0f, 0.0f));
        mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        return create_plane(asset::material::black_granite, mvm);
    }

    engine::component::JointAnimatorComponent create_animated_player ()
    {
        using namespace asset;
        using namespace asset::internal;

        engine::component::JointAnimatorComponent animator{&vao::animation::player_mesh, &vao::animation::player_animation};
        animator.program = program::animated_pbr;
        animator.vao = vao::animation::player;
        animator.count =  vao::animation::player_count;
        animator.model_view_matrix = glm::identity<glm::mat4>();
        animator.material = material::black_granite;

        return animator;
    }

    engine::component::GlMaterialComponent create_debug_light ()
    {
        using namespace asset;
        using namespace asset::internal;

        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::scale(mvm, glm::vec3{0.0625f, 0.0625f, 0.0625f});
        return {program::pbr, vao::sphere, vao::sphere_count, mvm, material::pile_of_skulls};
    }
}
