cmake_minimum_required(VERSION 3.10)
project(cglib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)

# Add the main executable
add_executable(cgm main.cc)

# Link the main executable with the libraries
target_link_libraries(cgm cglib)
