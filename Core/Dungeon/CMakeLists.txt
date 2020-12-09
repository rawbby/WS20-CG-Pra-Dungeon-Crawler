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

target_include_directories(${THIS} PRIVATE gui inc)

# add main (inc/src) source
target_sources(${THIS} PRIVATE
        inc/Statistics.h
        src/main.cpp)

# add gui (res) source
target_sources(${THIS} PRIVATE
        gui/MainWindow.cpp
        gui/MainWindow.hpp
        gui/MainWindow.ui
        gui/OpenGLWidget.cpp
        gui/OpenGLWidget.hpp
        res/index.qrc)

# include opengl
if (WIN32)
    target_link_libraries(${THIS} opengl32)
else ()
    target_link_libraries(${THIS} GL)
endif ()

# add qt6 components
target_link_libraries(${THIS} Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)

# add conan dependencies
target_link_libraries(${THIS} CONAN_PKG::glew CONAN_PKG::glm CONAN_PKG::spdlog)
