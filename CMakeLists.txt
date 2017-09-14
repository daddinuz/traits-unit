cmake_minimum_required(VERSION 3.1)
project(traits-unit)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast")
endif ()

#####
# Working directories
###
set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)
set(DEPENDENCY_PATH ${PROJECT_SOURCE_DIR}/deps)
set(EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/examples)

include_directories(${SOURCE_PATH})
file(GLOB _DEPENDENCY_DIRECTORIES ${DEPENDENCY_PATH}/*)
foreach (_file ${_DEPENDENCY_DIRECTORIES})
    if (IS_DIRECTORY ${_file})
        include_directories(${_file})
    endif ()
endforeach (_file ${_DEPENDENCY_DIRECTORIES})

#####
# Archive
###
file(GLOB HEADER_FILES ${SOURCE_PATH}/*.h)
file(GLOB SOURCE_FILES ${SOURCE_PATH}/*.c)
add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

#####
# Examples
###
file(GLOB EXAMPLE_SOURCES ${EXAMPLE_PATH}/*.c)
foreach (source_file ${EXAMPLE_SOURCES})
    get_filename_component(target ${source_file} NAME_WE)
    add_executable(${target} ${DEPENDENCY_PATH}/traits/traits.h ${source_file})
    target_link_libraries(${target} PRIVATE ${PROJECT_NAME})
endforeach (source_file ${EXAMPLE_SOURCES})
add_library(stack ${EXAMPLE_PATH}/stack/stack.h ${EXAMPLE_PATH}/stack/stack.c)
add_executable(test_stack ${DEPENDENCY_PATH}/traits/traits.h ${EXAMPLE_PATH}/stack/test_stack.c)
target_link_libraries(test_stack PRIVATE ${PROJECT_NAME} stack)
