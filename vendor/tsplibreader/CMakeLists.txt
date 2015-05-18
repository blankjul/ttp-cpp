cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR TSPLIBREADER)
project(${PROJECT_NAME_STR} C)


file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE HEADERS *.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_library(tsplibreader
    ${SOURCES}
)

