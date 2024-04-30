add_executable(server src/main.cpp src/Caen.cpp)
add_executable(test test.cpp src/Caen.cpp)
add_executable(usb_test usb_test.cpp)

target_include_directories(server PUBLIC include)
target_include_directories(test PUBLIC include)

target_link_libraries(server PUBLIC ${DIM_LIBRARY})
target_link_libraries(test PUBLIC ${DIM_LIBRARY})
target_link_libraries(server PUBLIC Threads::Threads)
target_link_libraries(test PUBLIC Threads::Threads)

