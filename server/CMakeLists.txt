add_executable(server src/main.cpp)
add_executable(test test.cpp)

include_directories(/usr/include/libusb-1.0)
link_directories(/usr/lib)

target_include_directories(server PUBLIC include)
target_include_directories(test PUBLIC include)

target_link_libraries(server PUBLIC ${DIM_LIBRARY} usb-1.0)
target_link_libraries(test PUBLIC ${DIM_LIBRARY} usb-1.0)