cmake_minimum_required(VERSION 3.16)

function(target_resources THIS)

    get_target_property(RUNTIME_OUTPUT_DIRECTORY ${THIS} RUNTIME_OUTPUT_DIRECTORY)

    foreach(RES_FILE IN LISTS ARGN)

        configure_file(
                ${CMAKE_CURRENT_SOURCE_DIR}/${RES_FILE}
                ${RUNTIME_OUTPUT_DIRECTORY}/${RES_FILE}
                COPYONLY)

    endforeach()

endfunction()

function(target_resource_directory THIS DIRECTORY)

    get_target_property(RUNTIME_OUTPUT_DIRECTORY ${THIS} RUNTIME_OUTPUT_DIRECTORY)
    file(GLOB_RECURSE RES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/**/*.*)

    foreach(RES_FILE IN LISTS RES_FILES)

        file(RELATIVE_PATH RES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY} ${RES_FILE})

        configure_file(
                ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/${RES_FILE}
                ${RUNTIME_OUTPUT_DIRECTORY}/${DIRECTORY}/${RES_FILE}
                COPYONLY)

    endforeach()

endfunction()
