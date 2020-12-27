#pragma once

#include <engine/component/GlMaterialComponent.hpp>

namespace asset
{
    namespace internal
    {
        void init_materials ();
    }

    namespace material
    {
        [[maybe_unused]] inline engine::component::Material pile_of_skulls{};
        [[maybe_unused]] inline engine::component::Material black_granite{};
        [[maybe_unused]] inline engine::component::Material broken_limestone_brick_path{};
    }
}
