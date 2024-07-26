# Add subdirectories
add_subdirectory(algorithm)
add_subdirectory(basic)

add_library(cglib INTERFACE)
target_link_libraries(cglib INTERFACE cglib_basic cglib_algorithm)

