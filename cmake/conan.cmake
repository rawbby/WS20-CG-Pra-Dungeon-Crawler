cmake_minimum_required(VERSION 3.16)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conan.cmake)
    file(DOWNLOAD
            https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake
            ${CMAKE_BINARY_DIR}/conan.cmake
            TLS_VERIFY ON)
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES glew/2.1.0   BASIC_SETUP CMAKE_TARGETS)
conan_cmake_run(REQUIRES glm/0.9.9.8  BASIC_SETUP CMAKE_TARGETS)
conan_cmake_run(REQUIRES spdlog/1.8.1 BASIC_SETUP CMAKE_TARGETS)
