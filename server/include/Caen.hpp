#pragma once

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

/// @brief  Class representing the CAEN power supply device
class Caen {
   private:
    static constexpr size_t BUFF_SIZE = 256;
    int _fd;
    termios _tty;

   public:
    Caen() {
        // Open the serial port
        _fd = open("/dev/ttyUSB0", O_RDWR);
        if (_fd == -1) {
            std::cerr << "Error opening serial port." << std::endl;
            exit(1);
        }

        // Configure the serial port
        memset(&_tty, 0, sizeof(_tty));
        if (tcgetattr(_fd, &_tty) != 0) {
            std::cerr << "Error getting serial port attributes." << std::endl;
            exit(1);
        }

        // Baud rate 9600
        cfsetospeed(&_tty, B9600);
        cfsetispeed(&_tty, B9600);

        // Parity: none
        _tty.c_cflag &= ~PARENB;

        // Stop bit: 1
        _tty.c_cflag &= ~CSTOPB;

        // Clear size setting
        _tty.c_cflag &= ~CSIZE;

        // Data bits: 8
        _tty.c_cflag |= CS8;

        // Enable reading and ignore modem control lines
        _tty.c_cflag |= CREAD | CLOCAL;

        // Flow control: XON/XOFF, IXANY - any character will restart stopped output ?
        _tty.c_iflag |= IXON | IXOFF | IXANY;

        // Set input mode (non-canonical, no echo)
        _tty.c_lflag &= ~(
            // ICANON |
            ECHO |
            ECHOE |
            ISIG);

        // Set output mode (raw output)
        _tty.c_oflag &= ~OPOST;

        // Set timeout for read operations
        _tty.c_cc[VMIN] = 0;
        _tty.c_cc[VTIME] = 10;  // 1 second timeout

        if (tcsetattr(_fd, TCSANOW, &_tty) != 0) {
            std::cerr << "Error setting serial port attributes." << std::endl;
            exit(1);
        }
    }

    bool sendMessage(std::string message) {
        char inputBuffer[BUFF_SIZE] = {};
        memcpy(inputBuffer, message.c_str(), message.size());
        inputBuffer[message.size()] = '\r';
        inputBuffer[message.size() + 1] = '\n';
        ssize_t bytesWritten = write(_fd, inputBuffer, message.size() + 2);
        if (bytesWritten < 0) {
            std::cerr << "Error writing to serial port." << std::endl;
            return false;
        }
        return true;
    }

    std::string readMessage() {
        char buffer[BUFF_SIZE] = {};
        ssize_t bytes_read = read(_fd, buffer, BUFF_SIZE - 1);
        if (bytes_read < 0) {
            std::cerr << "Error reading from serial port." << std::endl;
            return "";
        }
        buffer[bytes_read] = '\0';  // Null terminate the string
        return std::string(buffer);
    }

    ~Caen() {
        close(_fd);
    }
};