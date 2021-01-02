cmake_minimum_required(VERSION 3.18)

set(THIS FromUnrealPbr)

add_executable(${THIS})
set_compile_options(${THIS})
set_compile_warnings(${THIS})
deployqt(${THIS})

target_include_directories(${THIS} PRIVATE src)

# add main (src) source
target_sources(${THIS} PRIVATE
        Main.cpp)

# add qt6 dependencies
target_link_libraries(${THIS}
        Qt6::Core
        Qt6::Gui)

# add conan dependencies
target_link_libraries(${THIS}
        CONAN_PKG::spdlog)

target_link_libraries(${THIS} Assets)
