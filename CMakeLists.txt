cmake_minimum_required(VERSION 3.10)
project(Codewars_Projects)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Get all immediate subdirectories (projects)
file(GLOB subdirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*)

set(projects "")

foreach(subdir ${subdirs})
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${subdir}")
        # Check if the subdirectory contains CMakeLists.txt
        if(EXISTS "${CMAKE_SOURCE_DIR}/${subdir}/CMakeLists.txt")
            add_subdirectory(${subdir})

            add_custom_target(run_${subdir}
                COMMAND ${subdir}
                DEPENDS ${subdir}
                WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                COMMENT "Run project ${subdir}"
            )
        endif()
    endif()
endforeach()

# Create a help target
add_custom_target(show_help
    COMMAND ${CMAKE_COMMAND} -E echo "Usage:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build build --target run_<project>   # Build and run a project"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build build --target list_projects   # List all projects"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build build --target help            # Show this help"
)
