#ifndef SUPL_SERVER_MISC_MEMBLOCK_HPP_INCLUDED
#define SUPL_SERVER_MISC_MEMBLOCK_HPP_INCLUDED

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iosfwd>

#include "../macros.hpp"

SUPL_SERVER_BEGIN_DECLS

/**
 * The class to represent a block of memory.
 *
 * @attention This is a value symmetric class, which means it is default by
 * copy not by reference.
 */
class memblock {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer_type;
    typedef std::size_t size_type;

public:
    memblock(void const *, std::size_t);

    template <typename T, std::size_t N>
    memblock(T (&a)[N]) : _M_buffer(sizeof(a)), _M_size(sizeof(a)) {
        byte const *p = reinterpret_cast<byte const *>(&a[0]);
        std::copy(p, p + sizeof(a[0]) * N, &_M_buffer[0]);
    }

    void const *address() const;

    void *address();

    std::size_t size() const;

    memblock &assign(void const *, std::size_t);

    memblock &append(void const *, std::size_t);

private:
    buffer_type _M_buffer;
    size_type _M_size;
};

extern std::ostream &operator<<(std::ostream &, memblock const &);

SUPL_SERVER_END_DECLS

#endif // SUPL_SERVER_MISC_MEMBLOCK_HPP_INCLUDED
