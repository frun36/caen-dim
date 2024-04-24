#include <chrono>
#include <iostream>
#include <thread>

#include "dim/dic.hxx"

// Blocking
int main() {
    DimRpcInfo rpc("CAEN/USB", -1);

    char cmd[] = "$BD:00,CMD:MON,PAR:BDNAME"; 

    while (true) {
        rpc.setData(cmd);
        std::cout << "RPC Value: " << rpc.getString() <<"\n";
        sleep(2);
    }
}