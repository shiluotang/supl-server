#ifndef SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED
#define SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED

#include <vector>
#include <stdexcept>
#include <utility>
#include <iosfwd>

#include "skeletons/asn_application.h"

#include "../macros.hpp"

SUPL_SERVER_BEGIN_DECLS

class xer_codec {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer_type;
public:
    template <typename T>
    static bool encode(::asn_TYPE_descriptor_t &td, T &instance, buffer_type &buffer) {
        return encode0(td, &instance, buffer, false);
    }

    template <typename T>
    static bool encode(::asn_TYPE_descriptor_t &td, T &instance, std::ostream &os) {
        return encode0(td, &instance, os, false);
    }

    template <typename T>
    static buffer_type encode(::asn_TYPE_descriptor_t &td, T &instance) {
        buffer_type buffer;
        if (!encode(instance, buffer))
            throw std::runtime_error("xer encode failed!");
        return buffer;
    }

    template <typename T>
    static std::string encode(::asn_TYPE_descriptor_t &td, T &instance) {
        std::stringstream ss;
        if (encode0(td, &instance, ss, true)) try {
            return ss.str();
        } catch (...) {
            throw;
        }
    }
private:
    /**
     * Encode ASN.1 struct into std::ostream.
     *
     * @param [in] td The ASN.1 element type descriptor.
     * @param [in] struct_ptr The ASN.1 element C struct pointer.
     * @param [in] throwable Whether to throw exception on error.
     * @return true on success, vice versa.
     */
    static bool encode0(::asn_TYPE_descriptor_t &td, void *struct_ptr, std::ostream &os, bool throwable);
    static bool encode0(::asn_TYPE_descriptor_t&, void*, buffer_type&, bool);

    static void* decode0(::asn_TYPE_descriptor_t&, void const*, size_t, bool);
    static void* decode0(::asn_TYPE_descriptor_t&, std::string const&, bool);
    static void* decode0(::asn_TYPE_descriptor_t&, buffer_type const&, bool);
};

class uper_codec {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> buffer_type;
public:
    template <typename T>
    bool encode(::asn_TYPE_descriptor_t &td, T &instance, buffer_type &buffer) {
        // TODO not implemented yet!
        return true;
    }

    template <typename T>
    buffer_type encode(::asn_TYPE_descriptor_t &td, T &instance) {
        // TODO not implemented yet!
        return buffer_type();
    }

private:
    static bool encode0(::asn_TYPE_descriptor_t&, void*, buffer_type&, bool);
};

SUPL_SERVER_END_DECLS

#endif // SUPL_SERVER_ASN1C_CODEC_HPP_INCLUDED
