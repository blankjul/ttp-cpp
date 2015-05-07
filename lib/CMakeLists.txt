include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor/LKH-2.0.7/SRC/INCLUDE)


file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

add_library(ttp ${SOURCES} ${HEADERS})
target_link_libraries(ttp lkh)
install (TARGETS ttp ARCHIVE DESTINATION bin)

