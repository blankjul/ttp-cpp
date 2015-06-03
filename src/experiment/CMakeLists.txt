include_directories(${CMAKE_SOURCE_DIR}/vendor/tclap-1.2.1/include)
include_directories(${CMAKE_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_SOURCE_DIR}/src/algorithm)
include_directories(${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include)



ADD_DEFINITIONS(-std=c++11)
file(GLOB_RECURSE SOURCES *.cpp)


add_library(experiment SHARED ${SOURCES} ${HEADERS})

add_executable(experiment_
    Experiment.cpp
)
target_link_libraries(experiment_ experiment ttp algorithm)

