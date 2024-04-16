add_executable(client src/main.cpp)

set_target_properties(client PROPERTIES CXX_STANDARD 20)

target_include_directories(client PUBLIC include /home/frun/AGH/CERN/dim_v20r37)
target_link_directories(client PUBLIC /home/frun/AGH/CERN/dim_v20r37/linux)
target_link_libraries(client PUBLIC dim)