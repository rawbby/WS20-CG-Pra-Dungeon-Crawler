cmake_minimum_required(VERSION 3.18)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/target_resources.cmake)
    file(DOWNLOAD
            https://raw.githubusercontent.com/rawbby/CMakeTargetResources/master/target_resources.cmake
            ${CMAKE_BINARY_DIR}/target_resources.cmake
            TLS_VERIFY ON)
endif ()

include(${CMAKE_BINARY_DIR}/target_resources.cmake)
