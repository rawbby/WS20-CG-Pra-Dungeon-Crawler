cmake_minimum_required(VERSION 3.18)

set(THIS Engine)

add_library(${THIS} STATIC)
set_compile_options(${THIS})
set_compile_warnings(${THIS})

target_sources(${THIS} PUBLIC
        inc/engine/component/DynamicCollisionCircle.hpp
        inc/engine/component/GlBlendMaterialComponent.hpp
        inc/engine/component/GlMaterialComponent.hpp
        inc/engine/component/GlRenderComponent.hpp
        inc/engine/component/PositionComponent.hpp
        inc/engine/component/StaticCollisionLine.hpp

        inc/engine/service/CollisionService.hpp
        inc/engine/service/RenderService.hpp
        inc/engine/service/ShadowMapService.hpp

        inc/engine/Entity.hpp
        inc/engine/Game.hpp)

target_sources(${THIS} PRIVATE
        src/CollisionService.cpp
        src/RenderService.cpp
        src/ShadowMapService.cpp)

target_include_directories(${THIS} PUBLIC inc)

target_link_libraries(${THIS} PUBLIC
        $<${WIN32}:opengl32>
        $<$<NOT:${WIN32}>:GL>
        CONAN_PKG::glew
        CONAN_PKG::glm)

target_link_libraries(${THIS} PRIVATE
        CONAN_PKG::entt
        CONAN_PKG::spdlog)
