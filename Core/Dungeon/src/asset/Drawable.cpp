#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Drawable.hpp>

namespace
{
    asset::MaterialDrawable create_pile_of_skulls_plane (glm::mat4 mvm = {})
    {
        using namespace asset;
        using namespace asset::internal;
        return {program::material, vao::plane, vao::plane_count, mvm, material::pile_of_skulls};
    }

    asset::MaterialDrawable create_broken_limestone_brick_path_plane (glm::mat4 mvm = {})
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
        [[maybe_unused]] MaterialDrawable create_floor ()
        {
            return create_pile_of_skulls_plane(internal::mvm::id);
        }

        [[maybe_unused]] MaterialDrawable create_wall_back ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270);
        }

        [[maybe_unused]] MaterialDrawable create_wall_right ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z270);
        }

        [[maybe_unused]] MaterialDrawable create_wall_front ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z180);
        }

        [[maybe_unused]] MaterialDrawable create_wall_left ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::rot_x270_z90);
        }

        [[maybe_unused]] MaterialDrawable create_wall_top ()
        {
            return create_broken_limestone_brick_path_plane(internal::mvm::tra_y1);
        }
    }
}
