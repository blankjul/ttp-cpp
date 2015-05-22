cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR travelling-thief-problem)
project(${PROJECT_NAME_STR} C CXX)


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})



ADD_SUBDIRECTORY(vendor)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(doc)










