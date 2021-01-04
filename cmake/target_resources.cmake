cmake_minimum_required(VERSION 3.18)

function(target_resources THIS)

    get_target_property(RUNTIME_OUTPUT_DIRECTORY ${THIS} RUNTIME_OUTPUT_DIRECTORY)

    foreach (RES_FILE IN LISTS ARGN)

        if(IS_ABSOLUTE ${RES_FILE})
            file(RELATIVE_PATH PATH ${CMAKE_CURRENT_SOURCE_DIR} ${RES_FILE})
        endif()

        add_custom_command(TARGET ${THIS} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/${RES_FILE}
                ${RUNTIME_OUTPUT_DIRECTORY}/${RES_FILE})

    endforeach ()

endfunction()

function(target_resource_directories THIS)

    get_target_property(RUNTIME_OUTPUT_DIRECTORY ${THIS} RUNTIME_OUTPUT_DIRECTORY)

    foreach (DIRECTORY IN LISTS ARGN)

        if(IS_ABSOLUTE ${DIRECTORY})
            file(RELATIVE_PATH PATH ${CMAKE_CURRENT_SOURCE_DIR} ${DIRECTORY})
        endif()

        add_custom_command(TARGET ${THIS} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}
                ${RUNTIME_OUTPUT_DIRECTORY}/${DIRECTORY})

    endforeach ()

endfunction()

function(target_tar_gz_resources THIS)

    get_target_property(RUNTIME_OUTPUT_DIRECTORY ${THIS} RUNTIME_OUTPUT_DIRECTORY)

    foreach (PATH IN LISTS ARGN)

        if(IS_ABSOLUTE ${PATH})
            file(RELATIVE_PATH PATH ${CMAKE_CURRENT_SOURCE_DIR} ${PATH})
        endif()

        get_filename_component(TAR_DIR ${PATH} DIRECTORY)
        get_filename_component(TAR_NAME ${PATH} NAME)

        add_custom_command(TARGET ${THIS} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/${PATH}
                ${RUNTIME_OUTPUT_DIRECTORY}/${PATH})

        add_custom_command(TARGET ${THIS} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E tar xz ${TAR_NAME}
                WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY}/${TAR_DIR})

        if (${CMAKE_BUILD_TYPE} STREQUAL Release)
            add_custom_command(TARGET ${THIS} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E rm -f
                    ${RUNTIME_OUTPUT_DIRECTORY}/${PATH})
        endif ()

    endforeach ()

endfunction()
