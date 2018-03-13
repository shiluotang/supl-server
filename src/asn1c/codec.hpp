#ifndef SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED
#define SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED

#include <vector>
#include <stdexcept>
#include <utility>
#include <iosfwd>

#include "../macros.hpp"

#include "skeletons/asn_application.h"

SUPL_SERVER_BEGIN_DECLS

class memblock {
public:
    memblock() { }
    virtual ~memblock() {}
private:
};

class xer_codec {
public:
    typedef unsigned char ubyte;
    typedef std::vector<ubyte> buffer_t;
public:
    template <typename T>
    static bool encode(::asn_TYPE_descriptor_t &td, T &instance, buffer_t &bytes) {
        return true;
    }

    template <typename T>
    static buffer_t encode(::asn_TYPE_descriptor_t &td, T &instance) {
        buffer_t buffer;
        if (!encode(instance, buffer))
            throw std::runtime_error("xer encode failed!");
        return buffer;
    }
private:
    static ::asn_enc_rval_t encode0(::asn_TYPE_descriptor_t&, void*, std::ostream&);
    static ::asn_enc_rval_t encode0(::asn_TYPE_descriptor_t&, void*, buffer_t&);
};

SUPL_SERVER_END_DECLS

#endif // SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED
