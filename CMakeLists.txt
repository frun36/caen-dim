cmake_minimum_required(VERSION 3.10)
project(caen)

set(CMAKE_CXX_COMPILER g++-13)

# Client
add_subdirectory(client)

# Server
add_subdirectory(server)