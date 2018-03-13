#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>

#include "../src/server/supl-server.hpp"

#include <openssl/sha.h>

int main(int argc, char* argv[]) try {
    ::SHA256_CTX ctx;
    ::SHA256_Init(&ctx);

    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN CAUSE>" << std::endl;
    return EXIT_FAILURE;
}
