include_directories(${CMAKE_CURRENT_SOURCE_DIR})


file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

add_library(libttp ${SOURCES} ${HEADERS})
install (TARGETS libttp ARCHIVE DESTINATION bin)