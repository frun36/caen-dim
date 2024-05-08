#include <chrono>
#include <iostream>
#include <thread>

#include "dim/dic.hxx"

// Blocking
int main() {
    DimRpcInfo rpc("CAEN/USB", -1);

    char cmd[] = "$BD:00,CH:0,CMD:SET,PAR:VSET,VAL:000.00"; 

    while (true) {
        rpc.setData(cmd);
        std::cout << "RPC Value: " << rpc.getString() <<"\n";
        sleep(2);
    }
}
