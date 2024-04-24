// For testing the USB communication

#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

// Function to send a command to the device
bool send_command(int fd, const char* command) {
    ssize_t bytes_written = write(fd, command, strlen(command));
    if (bytes_written < 0) {
        std::cerr << "Error writing to serial port." << std::endl;
        return false;
    }
    return true;
}

// Function to read the response from the device
bool read_response(int fd, char* buffer, size_t bufferSize) {
    ssize_t bytes_read = read(fd, buffer, bufferSize - 1);
    if (bytes_read < 0) {
        std::cerr << "Error reading from serial port." << std::endl;
        return false;
    }
    buffer[bytes_read] = '\0'; // Null terminate the string
    return true;
}

int main() {
    // Open the serial port
    int fd = open("/dev/ttyUSB0", O_RDWR);
    if (fd == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        return 1;
    }
    std::cout << "Serial port opened\n";

    // Configure the serial port
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error getting serial port attributes." << std::endl;
        return 1;
    }
    std::cout << "Serial port attributes ok\n";

    // Baud rate 9600
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    // Parity: none
    tty.c_cflag &= ~PARENB;

    // Stop bit: 1
    tty.c_cflag &= ~CSTOPB;

    // Clear size setting
    tty.c_cflag &= ~CSIZE;

    // Data bits: 8
    tty.c_cflag |= CS8;

    // Enable reading and ignore modem control lines
    tty.c_cflag |= CREAD | CLOCAL;

    // Flow control: XON/XOFF, IXANY - any character will restart stopped output ?
    tty.c_iflag |= IXON | IXOFF | IXANY;

    // Set input mode (non-canonical, no echo)
    tty.c_lflag &= ~(
        // ICANON | 
        ECHO |
        ECHOE |
        ISIG
        );

    // Set output mode (raw output)
    tty.c_oflag &= ~OPOST;

    // Set timeout for read operations
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10; // 1 second timeout

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting serial port attributes." << std::endl;
        return 1;
    }
    std::cout << "Serial port attributes set\n";

    // Send command to the device
    const char* command = "$BD:00,CMD:MON,PAR:BDNAME\r\n"; // Example command
    if (!send_command(fd, command)) {
        close(fd);
        return 1;
    }

    std::cout << "Command sent\n";

    // Read response from the device
    char buffer[256];
    if (!read_response(fd, buffer, sizeof(buffer))) {
        close(fd);
        return 1;
    }
    
    // Print the response
    std::cout << "Received: " << buffer << std::endl;

    // Close the serial port
    close(fd);
    return 0;
}