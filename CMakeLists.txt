cmake_minimum_required(VERSION 3.10)
project(traits-unit)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror -pedantic-errors")

# dependencies
include_directories(deps)

# archive
include_directories(sources)
include(sources/build.cmake)

# tests
include(tests/unit/build.cmake)
