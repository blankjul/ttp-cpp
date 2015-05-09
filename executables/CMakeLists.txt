include_directories(${CMAKE_SOURCE_DIR}/vendor/tclap-1.2.1/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)


ADD_DEFINITIONS(
    -std=c++11
)


add_executable(ttpsolver
    ttpsolver.cpp
)
target_link_libraries(ttpsolver ttp)


add_executable(ttpgenerator
    ttpgenerator.cpp
)
target_link_libraries(ttpgenerator ttp)



install (TARGETS ttpsolver RUNTIME DESTINATION bin)
install (TARGETS ttpgenerator RUNTIME DESTINATION bin)
