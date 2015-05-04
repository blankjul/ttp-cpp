# Add test cpp file
add_executable(ttp
    main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(ttp libttp)
install (TARGETS ttp RUNTIME DESTINATION bin)
