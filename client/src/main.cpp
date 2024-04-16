#include <chrono>
#include <iostream>
#include <thread>

#include "dim/dic.hxx"

// Blocking
int main() {
    int rpcValue = 69;
    DimRpcInfo rpcMonVset("CAEN/MON_VSET", -1);
    DimRpcInfo rpcSetVmin("CAEN/SET_VMIN", -1);

    char buff[] = "dupatest"; 

    while (true) {
        rpcMonVset.setData(buff);
        rpcSetVmin.setData(buff);
        std::cout << "RPC Value: " << rpcMonVset.getString() << " " << rpcSetVmin.getString() << "\n";
        sleep(2);
    }

    // pause();
}