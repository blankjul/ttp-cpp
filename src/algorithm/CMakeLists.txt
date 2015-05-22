include_directories(${CMAKE_SOURCE_DIR}/src/algorithm)
include_directories(${CMAKE_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_SOURCE_DIR}/vendor/combo)


file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

ADD_DEFINITIONS(-std=c++11)


add_library(algorithm ${SOURCES} ${HEADERS})
target_link_libraries(algorithm ttp combo)
install (TARGETS algorithm ARCHIVE DESTINATION bin)

