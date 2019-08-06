#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include <openssl/sha.h>

#include "../src/asn1c/module/supl-2.0.3/SUPLSTART.h"

#include "../src/misc/memblock.hpp"
#include "../src/misc/utils.hpp"
#include "../src/server/supl-server.hpp"
#include "../src/asn1c/codec.hpp"

class transport {
public:
    transport() {
    }
    virtual ~transport() {}
private:
    int _M_sock;
};

int main(int argc, char* argv[]) try {
    using namespace std;
    using namespace org::sqg::supl;

    uint64_t p = 56;
    INTEGER_t x;
    memset(&x, 0, sizeof(x));
    x.buf = reinterpret_cast<uint8_t*>(&p);
    x.size = sizeof(p);
    uper_codec::buffer_type const &buffer = uper_codec::encode(asn_DEF_INTEGER, x);
    memblock encoded(&buffer[0], buffer.size());
    cout << boolalpha << encoded << endl;
    cout << "sizeof(long) = " << sizeof(long) << endl;
    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN CAUSE>" << std::endl;
    return EXIT_FAILURE;
}
