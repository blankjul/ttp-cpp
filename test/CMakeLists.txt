###############################################################################
# Include directories
###############################################################################
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/algorithm)
include_directories(${CMAKE_SOURCE_DIR}/vendor/generators)
include_directories(${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include)



###############################################################################
# C++ 11
###############################################################################
ADD_DEFINITIONS(-std=c++11)


###############################################################################
# Google Mock & Test
###############################################################################
set(GMOCK_ROOT ${CMAKE_SOURCE_DIR}/vendor/gmock-1.7.0)
include_directories(${GMOCK_ROOT}/include)
include_directories(${GMOCK_ROOT}/gtest/include)



###############################################################################
# Build and Link
###############################################################################
file(GLOB_RECURSE SOURCES *.cpp)



add_executable(tests
    ${SOURCES}
)

target_link_libraries(tests
    ttp
    algorithm
    experiment
    gmock
    gtest
)

add_test(NAME tests COMMAND tests)




