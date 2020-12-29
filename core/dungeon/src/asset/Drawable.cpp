#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Drawable.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace
{
    engine::component::GlMaterialComponent create_plane (engine::component::Material material, glm::mat4 mvm)
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::pbr, vao::plane, vao::plane_count, mvm, material};
    }
}

namespace asset
{
    namespace internal
    {
        void init_drawables ()
        {
        }
    }

    namespace drawable
    {
        [[maybe_unused]]  engine::component::GlMaterialComponent create_floor ()
        {
            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            return create_plane(asset::material::dirty_hammered_copper, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_back ()
        {
            auto mvm = glm::identity<glm::mat4>();
            return create_plane(asset::material::black_granite, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_right ()
        {
            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            return create_plane(asset::material::broken_limestone_brick_path, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_front ()
        {
            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::rotate(mvm, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            return create_plane(asset::material::broken_limestone_brick_path, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_left ()
        {
            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::rotate(mvm, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            return create_plane(asset::material::chunky_wet_gravel_and_dirt, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_top ()
        {
            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::translate(mvm, glm::vec3(0.0f, 1.0f, 0.0f));
            mvm = glm::rotate(mvm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            return create_plane(asset::material::black_granite, mvm);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_player ()
        {
            using namespace asset;
            using namespace asset::internal;

            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::scale(mvm, glm::vec3{0.125f, 0.125f, 0.125f});
            return {program::material, vao::sphere, vao::sphere_count, mvm, material::black_granite};
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_debug_light ()
        {
            using namespace asset;
            using namespace asset::internal;

            auto mvm = glm::identity<glm::mat4>();
            mvm = glm::scale(mvm, glm::vec3{0.0625f, 0.0625f, 0.0625f});
            return {program::material, vao::sphere, vao::sphere_count, mvm, material::pile_of_skulls};
        }
    }
}
