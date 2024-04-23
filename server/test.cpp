#include "Caen.hpp"

int main() {
    Caen caen;
    caen.sendMessage("$BD:00,CMD:MON,PAR:BDNAME");
    std::string response = caen.readMessage();
    std::cout << response;
    return 0;
}