# Add test cpp file
add_executable(ttp-solver
    main.cpp
)


include_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(ttp-solver ttp)



install (TARGETS ttp-solver RUNTIME DESTINATION bin)
