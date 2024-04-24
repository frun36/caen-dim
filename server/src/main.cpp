#include <iostream>
#include <string>

#include "dim/dis.hxx"

#include "CaenRpc.hpp"


int main() {
    Caen caen;
    CaenRpc caenRpc("CAEN/USB", caen);

    std::cout << "Created RPC\n";
    DimServer::start("CAEN");
    std::cout << "Server started\n";
    while (true)
        pause();
}