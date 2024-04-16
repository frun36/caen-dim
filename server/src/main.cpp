#include <iostream>
#include <string>

#include "dim/dis.hxx"

class RpcTest : public DimRpc {
   private:
    int computations(int n) {
        for (int i = 0; i < 1e8 * n; i++) {
            n *= 2;
            n += 1;
            n /= 2;
        }

        return n;
    }

    void rpcHandler() {
        int val = getInt();
        std::cout << "Received " << val << "\n";
        val = computations(val);
        setData(val);
        std::cout << "Finished computations\n";
    }

   public:
    RpcTest(const char *name)
        : DimRpc(name, "I", "I"){};
};

int main() {
    RpcTest test("TESTRPC/TEST");

    DimServer::start("TESTRPC");
    while (1)
        pause();
}