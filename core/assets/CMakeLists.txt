cmake_minimum_required(VERSION 3.18)

set(THIS Assets)

add_library(${THIS} STATIC)
set_compile_options(${THIS})
set_compile_warnings(${THIS})

target_include_directories(${THIS} PUBLIC inc)

target_sources(${THIS} PUBLIC
        inc/asset/Asset.hpp
        inc/geometries/Plane.hpp
        inc/geometries/Sphere.hpp
        inc/resource/PbrMaterial.hpp
        inc/resource/UnrealPbrMaterial.hpp)

target_sources(${THIS} PRIVATE
        src/GlMaterialComponent.cpp
        src/Material.cpp
        src/Program.cpp
        src/Vao.cpp)

target_resource_directories(${THIS} res/glsl)
target_tar_gz_resources(${THIS}
        res/materials/gametextures/BlackGranite.tar.gz
        res/materials/gametextures/BlackOstrichHideWrinkles2.tar.gz
        res/materials/gametextures/BrokenLimestoneBrickPath.tar.gz
        res/materials/gametextures/ChunkyWetGravelAndDirt.tar.gz
        res/materials/gametextures/Clay01.tar.gz
        res/materials/gametextures/CrackedRedCeramicRoof.tar.gz
        res/materials/gametextures/DirtyHammeredCopper.tar.gz
        res/materials/gametextures/PileOfSkulls.tar.gz
        res/materials/gametextures/WhiteWoolCloth.tar.gz
        res/materials/gametextures/WoolWovenCarpetStripedBurgundy.tar.gz)

target_link_libraries(${THIS} PRIVATE
        Qt6::Core
        Qt6::Gui
        CONAN_PKG::spdlog)

target_link_libraries(${THIS} PUBLIC
        $<${WIN32}:opengl32>
        $<$<NOT:${WIN32}>:GL>
        CONAN_PKG::glew
        CONAN_PKG::glm
        Engine)
