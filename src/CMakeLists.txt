cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR travelling-thief-problem)
project(${PROJECT_NAME_STR} C CXX)

include_directories(${CMAKE_SOURCE_DIR}/vendor/jMetalCpp/src)


ADD_SUBDIRECTORY(algorithm)
ADD_SUBDIRECTORY(executables)
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(experiment)











