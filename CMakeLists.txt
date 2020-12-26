cmake_minimum_required(VERSION 3.16)

project(DungeonCrawler LANGUAGES CXX)

include(cmake/set_compile_options.cmake)
include(cmake/set_compile_warnings.cmake)
include(cmake/deployqt.cmake)

include(cmake/conan.cmake)
add_subdirectory(core/dungeon)
