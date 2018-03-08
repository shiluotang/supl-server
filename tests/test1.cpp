#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>

#include "../src/supl-server.hpp"

int main(int argc, char* argv[]) try {
    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN CAUSE>" << std::endl;
    return EXIT_FAILURE;
}
