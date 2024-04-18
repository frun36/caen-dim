#pragma once

#include <libusb-1.0/libusb.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

/// @brief  Class representing the CAEN power supply device
class Caen {
   private:
    static constexpr uint16_t VENDOR_ID = 0x3277;
    static constexpr uint16_t PRODUCT_ID = 0x0010;
    static constexpr size_t BUFF_LEN = 64;

    libusb_context *_ctx;
    libusb_device_handle *_devHandle;

   public:
    Caen() {
        // Initialize libusb
        if (libusb_init(&_ctx) != LIBUSB_SUCCESS) {
            std::cerr << "Failed to initialize libusb\n";
            exit(1);
        }

        // Open USB device by vendor ID and product ID
        _devHandle = libusb_open_device_with_vid_pid(_ctx, VENDOR_ID, PRODUCT_ID);
        if (!_devHandle) {
            std::cerr << "Failed to open USB device" << std::endl;
            libusb_exit(_ctx);
            exit(1);
        }
    }

    void sendMessage(std::string message) {
        size_t dataSize = message.length() + 2;

        unsigned char data[BUFF_LEN] = {};

        std::memcpy(data, message.c_str(), dataSize - 2);

        data[dataSize - 2] = '\r';
        data[dataSize - 1] = '\n';

        int transferred = 0;
        // Arbitrary parameters, to be verified
        if (libusb_bulk_transfer(_devHandle, 0x02, data, dataSize, &transferred, 1000) != LIBUSB_SUCCESS) {
            std::cerr << "Failed to send message: " + message + '\n';
            return;
        }

        std::cout << "Message: " + message + " sent successfully\n";
    }

    std::string readMessage() {
        unsigned char buffer[BUFF_LEN] = {};

        int transferred = 0;
        // Arbitrary parameters, to be verified
        if (libusb_bulk_transfer(_devHandle, 0x81, buffer, BUFF_LEN, &transferred, 1000) != LIBUSB_SUCCESS) {
            std::cerr << "Failed to read message\n";
            return "";
        }

        std::string response(reinterpret_cast<char *>(buffer), transferred);
        return response;
    }

    ~Caen() {
        libusb_release_interface(_devHandle, 0);
        libusb_close(_devHandle);
        libusb_exit(_ctx);
    }
};