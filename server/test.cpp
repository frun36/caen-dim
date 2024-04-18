// For testing the USB communication

#include "Caen.hpp"

#include <string>
#include <iostream>

int main() {
    Caen caen;

    caen.sendMessage("BD:00,CMD:MON,PAR:BDNAME");
    std::string response = caen.readMessage();

    std::cout << "Received response: " << response << '\n';

    return 0;
}