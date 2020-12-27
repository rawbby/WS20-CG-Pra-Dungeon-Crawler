#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Drawable.hpp>

namespace
{
    engine::component::GlMaterialComponent create_wool_woven_carpet_striped_burgundy_plane (glm::mat4 mvm = {})
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::material, vao::plane, vao::plane_count, mvm, material::wool_woven_carpet_striped_burgundy};
    }

    engine::component::GlMaterialComponent create_broken_limestone_brick_path_plane (glm::mat4 mvm = {})
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::material, vao::plane, vao::plane_count, mvm, material::broken_limestone_brick_path};
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
            return create_wool_woven_carpet_striped_burgundy_plane(internal::mvm::id);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_back ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_right ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z270);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_front ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z180);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_left ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z90);
        }

        [[maybe_unused]]  engine::component::GlMaterialComponent create_wall_top ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::tra_y1);
        }
    }
}
