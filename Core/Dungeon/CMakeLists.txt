cmake_minimum_required(VERSION 3.16)

set(THIS dungeon)

find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${THIS})
set_compile_options(${THIS})
set_compile_warnings(${THIS})
deployqt(${THIS})

target_include_directories(${THIS} PRIVATE src)

# add main (src) source
target_sources(${THIS} PRIVATE

        src/asset/Asset.hpp
        src/asset/Drawable.cpp
        src/asset/Drawable.hpp
        src/asset/Material.cpp
        src/asset/Material.hpp
        src/asset/Mvm.cpp
        src/asset/Mvm.hpp
        src/asset/Program.cpp
        src/asset/Program.hpp
        src/asset/Vao.cpp
        src/asset/Vao.hpp

        src/engine/component/DynamicCollisionComponent.hpp
        src/engine/component/GlBlendMaterialComponent.hpp
        src/engine/component/GlMaterialComponent.hpp
        src/engine/component/GlRenderComponent.hpp
        src/engine/component/PositionComponent.hpp
        src/engine/component/StaticCollisionComponent.hpp
        src/engine/component/TranslationComponent.hpp

        src/engine/service/CollisionService.cpp
        src/engine/service/CollisionService.hpp
        src/engine/service/RenderService.cpp
        src/engine/service/RenderService.hpp

        src/engine/Game.cpp
        src/engine/Game.hpp

        src/geometries/PlaneBottom.hpp
        src/Main.cpp)

# add gui (res) source
target_sources(${THIS} PRIVATE
        src/gui/MainWindow.cpp
        src/gui/MainWindow.hpp
        src/gui/MainWindow.ui
        src/gui/OpenGLWidget.cpp
        src/gui/OpenGLWidget.hpp
        res/materials/index.qrc
        res/glsl/index.qrc)

# include opengl
if (WIN32)
    target_link_libraries(${THIS} opengl32)
else ()
    target_link_libraries(${THIS} GL)
endif ()

# add qt6 dependencies
target_link_libraries(${THIS}
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets)

# add conan dependencies
target_link_libraries(${THIS}
        CONAN_PKG::glew
        CONAN_PKG::glm
        CONAN_PKG::entt
        CONAN_PKG::spdlog)

# add internal dependencies
# target_link_libraries(${THIS} )
