#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "../src/misc/memblock.hpp"
#include "../src/misc/utils.hpp"
#include "../src/server/supl-server.hpp"
#include "../src/asn1c/module/supl-2.0.3/SUPLSTART.h"

#include <openssl/sha.h>

SUPL_SERVER_BEGIN_DECLS

std::ostream &operator<<(std::ostream &os, memblock const &block) {
    using namespace org::sqg::supl;

    typedef memblock::byte byte;

    int const WIDTH = 16;
    int const HALF_WIDTH = WIDTH / 2;
    ios_guarder guarder(os);
    size_t idx = 0;
    os << std::hex << std::uppercase << std::setfill('0');
    for (byte const *p = reinterpret_cast<byte const *>(block.address()),
                    *e = p + block.size();
         p != e; ++p, ++idx) {
        idx %= WIDTH;
        if (idx == 0 && p != block.address())
            os << std::endl;
        os << ((idx >= HALF_WIDTH) ? " " : "") << std::setw(2) << ((*p) & 0xff)
           << ((idx < HALF_WIDTH) ? " " : "");
    }
    return os;
}

template <size_t N> class sha {
public:
    sha() {
        if (!::SHA_Init(&_M_context))
            throw std::runtime_error("failed to initialize sha context!");
    }

    sha &update(memblock const &block) {
        return update(block.address(), block.size());
    }

    sha &update(void const *data, size_t size) {
        if (!::SHA_Update(&_M_context, data, size))
            throw std::runtime_error("failed to append data!");
        return *this;
    }

    memblock complete() {
        unsigned char hash[SHA_DIGEST_LENGTH] = {0};
        complete(&hash[0]);
        return memblock(hash);
    }

    memblock complete(memblock const &block) {
        return update(block).complete();
    }

    sha &complete(unsigned char *hash) {
        unsigned char *md = hash;
        if (!::SHA_Final(md, &_M_context))
            throw std::runtime_error("failed to get hash result!");
        if (!::SHA_Init(&_M_context))
            throw std::runtime_error("failed to initialize sha context!");
        return *this;
    }

private:
    SHA_CTX _M_context;
};

#define XSHA_CTX(N) SHA##N##_CTX
#define XSHA_Init(N) SHA##N##_Init
#define XSHA_Update(N) SHA##N##_Update

#define XSHA_Final(N) SHA##N##_Final
#define XSHA_DIGEST_LENGTH(N) SHA##N##_DIGEST_LENGTH

#define SHA_TEMPLATE_IMPL(N)                                                   \
    template <> class sha<N> {                                                 \
    public:                                                                    \
        sha() {                                                                \
            if (!::XSHA_Init(N)(&_M_context))                                  \
                throw std::runtime_error("failed to initialize sha context!"); \
        }                                                                      \
                                                                               \
        sha &update(memblock const &block) {                                   \
            return update(block.address(), block.size());                      \
        }                                                                      \
                                                                               \
        sha &update(void const *data, size_t size) {                           \
            if (!::XSHA_Update(N)(&_M_context, data, size))                    \
                throw std::runtime_error("failed to append data!");            \
            return *this;                                                      \
        }                                                                      \
                                                                               \
        memblock complete() {                                                  \
            unsigned char hash[XSHA_DIGEST_LENGTH(N)] = {0};                   \
            complete(&hash[0]);                                                \
            return memblock(hash);                                             \
        }                                                                      \
                                                                               \
        memblock complete(memblock const &block) {                             \
            return update(block).complete();                                   \
        }                                                                      \
                                                                               \
        sha &complete(unsigned char *hash) {                                   \
            unsigned char *md = hash;                                          \
            if (!::XSHA_Final(N)(md, &_M_context))                             \
                throw std::runtime_error("failed to get hash result!");        \
            if (!::XSHA_Init(N)(&_M_context))                                  \
                throw std::runtime_error("failed to initialize sha context!"); \
            return *this;                                                      \
        }                                                                      \
                                                                               \
    private:                                                                   \
        XSHA_CTX(N) _M_context;                                                \
    };

SHA_TEMPLATE_IMPL(256)
SHA_TEMPLATE_IMPL(512)

SUPL_SERVER_END_DECLS

int main(int argc, char *argv[]) try {
    using namespace std;
    using namespace org::sqg::supl;

    std::string const &filename = "./config.log";

    char buffer[0xff];

    sha<256> algo;

    std::ifstream infile(filename, ios::binary);
    if (!infile)
        throw std::runtime_error(filename + " can't be open for read!");
    while (infile.read(&buffer[0], sizeof(buffer)))
        algo.update(&buffer[0], infile.gcount());
    if (infile.eof())
        std::cout << "sha256 of " << filename << " is " << std::endl << algo.complete() << std::endl;

    SUPLSTART_t start;

    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN CAUSE>" << std::endl;
    return EXIT_FAILURE;
}
