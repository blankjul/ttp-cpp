include_directories(${CMAKE_SOURCE_DIR}/vendor/gtest-1.7.0/include)

add_executable(tests main.cpp)

target_link_libraries(tests
    libttp
    gtest
)

