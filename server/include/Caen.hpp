#pragma once

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cerrno>

/// @brief  Class representing the CAEN power supply device
class Caen {
   private:
    static constexpr size_t BUFF_SIZE = 256;
    int _fd;
    termios _tty;

   public:
    /// @brief Constructor - initializes the connection
    Caen();

    /// @brief Appends CRLF to the message and sends it to the device
    void sendMessage(std::string message);

    /// @brief Reads message from the device and returns it as a `std::string` (blocking) 
    std::string readMessage();

    /// @brief Destructor - closes the connection
    ~Caen();
};