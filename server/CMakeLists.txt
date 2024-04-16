add_executable(server src/main.cpp)

set_target_properties(server PROPERTIES CXX_STANDARD 20)

target_include_directories(server PUBLIC include /home/frun/AGH/CERN/dim_v20r37)
target_link_directories(server PUBLIC /home/frun/AGH/CERN/dim_v20r37/linux)
target_link_libraries(server PUBLIC dim)