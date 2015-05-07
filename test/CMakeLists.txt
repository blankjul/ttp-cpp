
include_directories(${CMAKE_SOURCE_DIR}/vendor/gtest-1.7.0/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(tests
    ${SOURCES}
)

target_link_libraries(tests
    ttp
    gtest
)
install (TARGETS tests RUNTIME DESTINATION bin)




