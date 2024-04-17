#include <chrono>
#include <iostream>
#include <thread>

#include "dim/dic.hxx"

// Blocking
int main() {
    int rpcValue = 69;
    DimRpcInfo rpcMonBdname("CAEN/BDNAME/MON", -1);
    DimRpcInfo rpcMonVset("CAEN/VSET/MON", -1);
    DimRpcInfo rpcSetVset("CAEN/VSET/SET", -1);

    char buff[] = "test"; 

    while (true) {
        rpcMonBdname.setData(buff);
        rpcMonVset.setData(buff);
        rpcSetVset.setData(buff);
        std::cout << "RPC Value: " << rpcMonBdname.getString() << " " << rpcMonVset.getString() << " " << rpcSetVset.getString() << "\n";
        sleep(2);
    }

    // pause();
}