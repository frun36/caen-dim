#include <chrono>
#include <iostream>
#include <thread>

#include "dim/dic.hxx"

class Rpc : public DimRpcInfo {
    void rpcInfoHandler() {
        int valin = getInt();
        std::cout << "Callback RPC Received : " << valin << "\n";
    }

   public:
    Rpc(const char *name)
        : DimRpcInfo(name, -1){};
};

// int main() {
//     int rpcCBValue = 0;
//     Rpc rpcCB("TESTRPC/TEST");

//     while (1) {
//         rpcCB.setData(rpcCBValue);
//              std::cout << "DUPAAAA\n";
//              rpcCBValue++;
//         if (rpcCBValue > 8) break;
//         sleep(1);
//     }
// }

// Blocking
int main() {
    int rpcValue = 0;
    DimRpcInfo rpc("TESTRPC/TEST", -1);

    while (1) {
        rpc.setData(rpcValue);
        std::cout << "RPC Value: " << rpc.getInt() << "\n";
        rpcValue++;
        usleep(10);
    }
    // pause();
}