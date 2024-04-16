add_executable(server src/main.cpp)

set_target_properties(server PROPERTIES CXX_STANDARD 20)

target_include_directories(server PUBLIC include ../dim)
target_link_directories(server PUBLIC ../dim/linux)
target_link_libraries(server PUBLIC dim)