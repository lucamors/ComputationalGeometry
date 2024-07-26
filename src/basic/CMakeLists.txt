# Specify the source files in this directory
set(SOURCES
    Vector2D.cc
)

add_library(cglib_basic ${SOURCES})

target_include_directories(cglib_basic PUBLIC ${CMAKE_SOURCE_DIR}/include)
