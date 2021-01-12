#pragma once

#include <AnimatedMesh.hpp>

namespace dae_loader
{
    Animation load_animation (std::string_view path);
    AnimatedMesh load_animated_mesh (std::string_view path);
}
