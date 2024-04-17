cmake_minimum_required(VERSION 3.10)
project(caen)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

# Search for libdim library - has to be in /usr/local/lib/dim
find_library(DIM_LIBRARY
    NAMES dim
    PATHS /usr/local/lib/dim
)

# Search for libdim include directory - has to be /usr/local/include/dim
find_path(DIM_INCLUDE_DIR
    NAMES dic.hxx dis.hxx
    PATHS /usr/local/include/dim
)

# Check if libdim and its include directory were found
if (DIM_LIBRARY AND DIM_INCLUDE_DIR)
    message(STATUS "Found libdim library: ${DIM_LIBRARY}")
    message(STATUS "Found libdim include directory: ${DIM_INCLUDE_DIR}")

    # Include libdim include directory
    include_directories(${DIM_INCLUDE_DIR})
else()
    message(FATAL_ERROR "libdim library or include directory not found.")
endif()

# Client
add_subdirectory(client)

# Server
add_subdirectory(server)
