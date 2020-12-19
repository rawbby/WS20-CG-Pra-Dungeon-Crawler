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
        src/asset/Asset.cpp
        src/asset/Asset.hpp
        src/asset/Drawable.hpp
        src/asset/Util.cpp
        src/asset/Util.hpp
        src/common/FileUtil.cpp
        src/common/FileUtil.hpp
        src/geometries/Geometries.hpp
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

# add qt6 components
target_link_libraries(${THIS} Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)

# add conan dependencies
target_link_libraries(${THIS} CONAN_PKG::glew CONAN_PKG::glm CONAN_PKG::spdlog)
