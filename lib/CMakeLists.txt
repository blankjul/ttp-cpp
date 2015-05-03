include_directories(${CMAKE_CURRENT_SOURCE_DIR})


SET(SOURCE
    ttp.cpp
)
SET(HEADERS
    ttp.h
)

add_library( libttp ${SOURCE} ${HEADERS} )