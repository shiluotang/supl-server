#include <iomanip>
#include <ostream>

#include "utils.hpp"
#include "bytes.hpp"

SUPL_SERVER_BEGIN_DECLS

bytes::bytes(void const *data, std::size_t size)
    : _M_buffer(size)
    , _M_size(size) {
    byte const *p = reinterpret_cast<byte const*>(data);
    std::copy(p, p + size, &_M_buffer[0]);
}

void const* bytes::address() const { return &_M_buffer[0]; }

void* bytes::address() { return &_M_buffer[0]; }

std::size_t bytes::size() const { return _M_size; }

bytes &bytes::assign(void const *data, std::size_t size) {
    _M_buffer.resize(size);
    byte const *p = reinterpret_cast<byte const*>(data);
    std::copy(p, p + size, &_M_buffer[0]);
    _M_size = size;
    return *this;
}

bytes &bytes::append(void const *data, std::size_t size) {
    byte const *p = reinterpret_cast<byte const*>(data);
    _M_buffer.insert(_M_buffer.end(), p, p + size);
    _M_size += size;
    return *this;
}


std::ostream &operator<<(std::ostream &os, bytes const &block) {
    using namespace org::sqg::supl;

    typedef bytes::byte byte;

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

SUPL_SERVER_END_DECLS
