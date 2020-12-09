cmake_minimum_required(VERSION 3.16)

project(DungeonCrawler LANGUAGES CXX)

include(cmake/conan.cmake)

include(cmake/set_compile_options.cmake)
include(cmake/set_compile_warnings.cmake)
include(cmake/deployqt.cmake)

add_subdirectory(Core/Dungeon)

# option(BUILD_TESTING ON)
# if (BUILD_TESTING MATCHES ON)
#     enable_testing()
#     add_subdirectory(Test/Barracks)
# endif ()
