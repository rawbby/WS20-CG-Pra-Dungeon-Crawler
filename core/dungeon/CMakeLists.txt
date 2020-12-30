cmake_minimum_required(VERSION 3.18)

set(THIS DungeonCrawler)

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

        src/engine/service/CollisionService.cpp
        src/engine/service/CollisionService.hpp
        src/engine/service/RenderService.cpp
        src/engine/service/RenderService.hpp

        src/engine/Entity.hpp
        src/engine/Game.hpp

        src/geometries/Plane.hpp
        src/geometries/Sphere.hpp
        src/Main.cpp)

# add gui (res) source
target_sources(${THIS} PRIVATE
        src/gui/MainWindow.cpp
        src/gui/MainWindow.hpp
        src/gui/MainWindow.ui
        src/gui/OpenGLWidget.cpp
        src/gui/OpenGLWidget.hpp)

# copy resource folder to output directory
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
target_link_libraries(${THIS}
        resource)
