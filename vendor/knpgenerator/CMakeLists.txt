cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR knpgenerator)
project(${PROJECT_NAME_STR} C)

ADD_DEFINITIONS(
    -w
)

add_library(knpgenerator
    pisinger_generator.c
)

target_link_libraries(knpgenerator m)


