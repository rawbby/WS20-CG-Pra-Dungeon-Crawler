cmake_minimum_required(VERSION 3.16)

find_package(Qt6 COMPONENTS Core REQUIRED)

function(deployqt THIS)

    get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR ${QMAKE_EXE} DIRECTORY)

    if (WIN32)

        find_program(WINDEPLOYQT_EXE windeployqt HINTS ${QT_BIN_DIR})
        add_custom_command(TARGET ${THIS} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E env PATH=${QT_BIN_DIR} ${WINDEPLOYQT_EXE} $<TARGET_FILE:${THIS}>)
    else ()

        message(WARNING
                "No deployqt specified for target platform. "
                "This project currently only supports deployment for windows!")

    endif ()

endfunction()
