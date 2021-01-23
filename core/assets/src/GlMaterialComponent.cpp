#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

#include <glm/gtx/transform.hpp>

namespace
{
    engine::component::GlMaterialComponent create_plane (engine::component::Material material, glm::mat4 mvm)
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::pbr, vao::plane, vao::plane_lr, vao::plane_count, vao::plane_lr_count, mvm, material};
    }
}

namespace asset::material
{
    engine::component::GlMaterialComponent create_floor ()
    {
        auto mvm = glm::identity<glm::mat4>();
        mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        return create_plane(asset::material::chunky_wet_gravel_and_dirt, mvm);
    }

    engine::component::GlMaterialComponent create_wall_back ()
    {
        auto mvm = glm::identity<glm::mat4>();
        return create_plane(asset::material::broken_limestone_brick_path, mvm);
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
        return create_plane(asset::material::broken_limestone_brick_path, mvm);
    }
}
