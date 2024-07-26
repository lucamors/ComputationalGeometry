# Specify the source files in this directory
set(SOURCES
    ConvexHull.cc
)

# Create a library for this module
add_library(cglib_algorithm ${SOURCES})

# Link the library with the main src_lib
target_include_directories(cglib_algorithm PUBLIC ${CMAKE_SOURCE_DIR}/include)