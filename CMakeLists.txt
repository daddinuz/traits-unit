cmake_minimum_required(VERSION 3.0)
project(traits-unit)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast")
endif ()

#####
# Macro definitions
###
macro(get_subdirectories result current_directory)
    set(directory_list "")
    file(GLOB children RELATIVE ${current_directory} ${current_directory}/*)
    foreach (child ${children})
        if (IS_DIRECTORY ${current_directory}/${child})
            list(APPEND directory_list ${current_directory}/${child})
        endif ()
    endforeach ()
    set(${result} ${directory_list})
endmacro(get_subdirectories)

#####
# Variable definitions
###
set(DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/deps)
set(PROJECT_PATH ${PROJECT_SOURCE_DIR}/sources)
set(TESTS_PATH ${PROJECT_SOURCE_DIR}/tests)

file(GLOB PROJECT_HEADERS ${PROJECT_PATH}/*.h)
file(GLOB PROJECT_SOURCES ${PROJECT_PATH}/*.c)
file(GLOB UNIT_TEST_SOURCES ${TESTS_PATH}/unit/*.c)

#####
# Working directories
###
include_directories(${PROJECT_PATH})
include_directories(${DEPENDENCIES_PATH})

#####
# Archive
###
add_library(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})

#####
# Tests
###
enable_testing()
foreach (source_file ${UNIT_TEST_SOURCES})
    get_filename_component(target ${source_file} NAME_WE)
    add_executable(${target} ${source_file})
    target_link_libraries(${target} PRIVATE ${PROJECT_NAME})
    add_test(${target} ${target})
endforeach (source_file ${UNIT_TEST_SOURCES})
