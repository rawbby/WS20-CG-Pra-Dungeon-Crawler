cmake_minimum_required(VERSION 3.18)

set(THIS DaeLoader)

add_library(${THIS} STATIC)
set_compile_options(${THIS})
set_compile_warnings(${THIS})

target_include_directories(${THIS} PUBLIC inc)

target_sources(${THIS} PUBLIC
        inc/AnimatedMesh.hpp
        inc/DaeLoader.hpp
        src/DaeLoader.cpp)

target_resources(${THIS} dae/bone0.dae)

target_link_libraries(${THIS} PUBLIC
        CONAN_PKG::glm
        CONAN_PKG::assimp
        CONAN_PKG::spdlog)
