#include <iostream>
#include <string>

#include "dim/dis.hxx"

#include "CaenRpc.hpp"


int main() {
    CaenRpc a(CMD::MON, "BDNAME", true);
    CaenRpc b(CMD::MON, "VSET");
    CaenRpc c(CMD::SET, "VSET");


    std::cout << "Created RPCs\n";
    DimServer::start("CAEN");
    std::cout << "Server started\n";
    while (true)
        pause();
}