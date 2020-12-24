#pragma once

#include <glm/matrix.hpp>

namespace asset::internal
{
    void init_mvms ();

    namespace mvm
    {
        [[maybe_unused]] inline glm::mat4 id{};
        [[maybe_unused]] inline glm::mat4 rot_x270{};
        [[maybe_unused]] inline glm::mat4 rot_x270_z270{};
        [[maybe_unused]] inline glm::mat4 rot_x270_z180{};
        [[maybe_unused]] inline glm::mat4 rot_x270_z90{};
        [[maybe_unused]] inline glm::mat4 tra_y1{};
    }
}
