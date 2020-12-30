cmake_minimum_required(VERSION 3.18)

set(THIS resource)

add_library(${THIS} INTERFACE)

target_include_directories(${THIS} INTERFACE src)

target_sources(${THIS} INTERFACE
        src/resource/PbrMaterial.hpp
        src/resource/UnrealPbrMaterial.hpp)

target_link_libraries(${THIS} INTERFACE Qt6::Core Qt6::Gui)
target_link_libraries(${THIS} INTERFACE CONAN_PKG::spdlog)

set(THIS FromUnrealPbr)

add_executable(${THIS})
set_compile_options(${THIS})
set_compile_warnings(${THIS})
deployqt(${THIS})

target_include_directories(${THIS} PRIVATE src)

# add main (src) source
target_sources(${THIS} PRIVATE
        src/resource/PbrMaterial.hpp
        src/resource/UnrealPbrMaterial.hpp
        src/FromUnrealPbrMain.cpp)

# add qt6 dependencies
target_link_libraries(${THIS}
        Qt6::Core
        Qt6::Gui)

# add conan dependencies
target_link_libraries(${THIS}
        CONAN_PKG::spdlog)
