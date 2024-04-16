add_executable(client src/main.cpp)

set_target_properties(client PROPERTIES CXX_STANDARD 20)

target_include_directories(client PUBLIC include ../dim)
target_link_directories(client PUBLIC ../dim/linux)
target_link_libraries(client PUBLIC dim)