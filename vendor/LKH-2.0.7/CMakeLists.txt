cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR LKH)
project(${PROJECT_NAME_STR} C)


file(GLOB_RECURSE SOURCES SRC/*.c)
file(GLOB_RECURSE HEADERS SRC/INCLUDE/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SRC/INCLUDE)

set(LIB_SOURCES ${SOURCES})
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/SRC/LKHmain.c)

add_library(lkh
    ${LIB_SOURCES}
)
target_link_libraries(lkh m)

add_executable(lkh_run
    SRC/LKHmain.c
)


target_link_libraries(lkh_run lkh)


