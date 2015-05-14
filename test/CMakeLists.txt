include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/vendor/gtest-1.7.0/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/vendor/LKH-2.0.7/SRC/INCLUDE)


ADD_DEFINITIONS(
    -std=c++11
)


#add_library(examples examples/test_examples.cpp)




file(GLOB_RECURSE SOURCES *.cpp)
add_executable(tests
    ${SOURCES}
)



target_link_libraries(tests
    ttp
    gtest
)
install (TARGETS tests RUNTIME DESTINATION bin)




