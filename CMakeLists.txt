cmake_minimum_required(VERSION 3.18)

project(DungeonCrawler LANGUAGES CXX)

include(cmake/set_compile_options.cmake)
include(cmake/set_compile_warnings.cmake)
include(cmake/deployqt.cmake)
include(cmake/target_resources.cmake)

include(cmake/conan.cmake)

conan_cmake_run(REQUIRES
        glew/2.1.0
        glm/0.9.9.8
        spdlog/1.8.1
        entt/3.5.2
        cgltf/1.9
        BASIC_SETUP CMAKE_TARGETS)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        OpenGLWidgets
        REQUIRED)

add_subdirectory(core/engine)
add_subdirectory(core/assets)
add_subdirectory(core/dungeon)

add_subdirectory(tools/from_unreal_pbr)
