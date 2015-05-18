include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor/LKH-2.0.7/SRC/INCLUDE)
include_directories(${CMAKE_SOURCE_DIR}/vendor/combo)
include_directories(${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/tsplibreader)


file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

ADD_DEFINITIONS(
    -std=c++11
)



add_library(ttp ${SOURCES} ${HEADERS})
target_link_libraries(ttp lkh combo jsoncpp_lib_static tsplibreader)
install (TARGETS ttp ARCHIVE DESTINATION bin)

