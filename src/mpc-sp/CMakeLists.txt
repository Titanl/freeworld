cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/dist/lib/")

add_library (
    "freeworld-mpc-sp"
    SHARED
    "instance.cpp"
    "handle_mi.cpp"
    "media_manager.cpp"
)
