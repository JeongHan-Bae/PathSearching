cmake_minimum_required(VERSION 3.24)

project(PathSearching)

# Add your source files
set(SOURCE_FILES City.cpp)

# Create a dynamic library from the source files
add_library(PathSearching SHARED ${SOURCE_FILES})

# Link your library with the main executable
target_link_libraries(test PathSearching)
