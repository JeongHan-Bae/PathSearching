cmake_minimum_required(VERSION 3.24)
project(Test)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the PathSearching library
set(PATH_SEARCHING_DIR "${CMAKE_SOURCE_DIR}/../PathSearching")
set(PATH_SEARCHING_LIB_DIR "${PATH_SEARCHING_DIR}/cmake-build-debug")

add_executable(Test main.cpp)

# Include the directory containing City.h
target_include_directories(Test PRIVATE "${PATH_SEARCHING_DIR}")
# Link against the PathSearching library
target_link_libraries(Test PRIVATE "${PATH_SEARCHING_LIB_DIR}/libPathSearching.dll")

# Set the working directory for the Test executable
set_target_properties(Test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
