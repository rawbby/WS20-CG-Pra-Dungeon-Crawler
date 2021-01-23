cmake_minimum_required(VERSION 3.18)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(THIS Dungeon)

add_executable(${THIS} src/gui/Scene001.hpp)
set_compile_options(${THIS})
set_compile_warnings(${THIS})
deployqt(${THIS})

target_include_directories(${THIS} PRIVATE src)

# add gui (res) source
target_sources(${THIS} PRIVATE
        src/gui/MainWindow.cpp
        src/gui/MainWindow.hpp
        src/gui/MainWindow.ui
        src/gui/OpenGLWidget.cpp
        src/gui/OpenGLWidget.hpp
        src/Main.cpp)

# include opengl
target_link_libraries(${THIS}
        $<${WIN32}:opengl32>
        $<$<NOT:${WIN32}>:GL>
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        CONAN_PKG::glew
        CONAN_PKG::glm
        CONAN_PKG::entt
        CONAN_PKG::spdlog
        Assets
        Engine)
