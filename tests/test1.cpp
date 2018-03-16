#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "../src/utils.hpp"
#include "../src/server/supl-server.hpp"
#include "../src/asn1c/module/supl-2.0.3/SUPLSTART.h"

#include <openssl/sha.h>

/**
 * The class to represent a block of memory.
 *
 * \@attention This is a value symmetric class, which means it is default by
 * copy not by reference.
 */
class memblock {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer_type;
    typedef std::size_t size_type;

public:
    memblock(void const *data, size_t size) : _M_buffer(size), _M_size(size) {
        byte const *p = reinterpret_cast<byte const *>(data);
        std::copy(p, p + size, &_M_buffer[0]);
    }

    template <typename T, size_t N>
    memblock(T (&a)[N]) : _M_buffer(sizeof(a)), _M_size(sizeof(a)) {
        byte const *p = reinterpret_cast<byte const *>(&a[0]);
        std::copy(p, p + sizeof(a[0]) * N, &_M_buffer[0]);
    }

    void const *address() const { return &_M_buffer[0]; }
    void *address() { return &_M_buffer[0]; }
    size_type size() const { return _M_size; }

    memblock &assign(void const *data, size_t size) {
        _M_buffer.resize(size);
        byte const *p = reinterpret_cast<byte const *>(data);
        std::copy(p, p + size, &_M_buffer[0]);
        _M_size = size;
        return *this;
    }

    memblock &append(void const *data, size_t size) {
        byte const *p = reinterpret_cast<byte const *>(data);
        _M_buffer.insert(_M_buffer.end(), p, p + size);
        _M_size += size;
        return *this;
    }

private:
    buffer_type _M_buffer;
    size_type _M_size;
};

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

int main(int argc, char *argv[]) try {
    using namespace std;
    using namespace org::sqg::supl;

    sha<256> algo;

    SUPLSTART_t start;

    return EXIT_SUCCESS;
} catch (std::exception const &e) {
    std::cerr << "[C++ exception] " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "[C++ exception] <UNKNOWN CAUSE>" << std::endl;
    return EXIT_FAILURE;
}
