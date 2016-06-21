cmake_minimum_required(VERSION 3.0)
project("BubbaRogueFort")

# Set flags
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLEW_STATIC")

# Compile BUBBA-3D
add_subdirectory(Bubba-3D)
add_subdirectory(src)