#include <iostream>
#include <string>

#include "dim/dis.hxx"

#include "caen.hpp"

#include <vector>
#include <any>

// class RpcTest : public DimRpc {
//    private:
//     int computations(int n) {
//         for (int i = 0; i < 1e8 * n; i++) {
//             n *= 2;
//             n += 1;
//             n /= 2;
//         }

//         return n;
//     }

//     void rpcHandler() {
//         int val = getInt();
//         std::cout << "Received " << val << "\n";
//         val = computations(val);
//         setData(val);
//         std::cout << "Finished computations\n";
//     }

//    public:
//     RpcTest(const char *name)
//         : DimRpc(name, "I", "I"){};
// };

int main() {
    // std::vector<std::any> vec;
    // vec.push_back(CaenRpc<CMD::MON, PAR::VSET>("CAEN/VSET"));
    // vec.push_back(CaenRpc<CMD::MON, PAR::VMIN>("CAEN/VMIN"));
    // vec.push_back(CaenRpc<CMD::MON, PAR::VMAX>("CAEN/VMAX"));

    CaenRpc<CMD::MON, PAR::VSET> a;
    CaenRpc<CMD::SET, PAR::VMIN> b;

    DimServer::start("CAEN");
    std::cout << "Server started\n";
    while (true)
        pause();
}