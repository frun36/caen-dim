add_executable(client src/main.cpp)

target_include_directories(client PUBLIC include)

target_link_libraries(client PUBLIC ${DIM_LIBRARY})
target_link_libraries(client PUBLIC Threads::Threads)
