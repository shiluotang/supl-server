#include <ostream>
#include <sstream>
#include <stdexcept>

#include "codec.hpp"

namespace {

    template <typename T>
    int encode_buffer_callback (const void *buffer, size_t size,
            void *application_specific_key) {
        typedef typename T::buffer_type buffer_type;
        typedef typename T::byte byte;
        if (!application_specific_key)
            return -1;
        buffer_type &storage = *reinterpret_cast<buffer_type*>(application_specific_key);
        byte const* p = reinterpret_cast<byte const*>(buffer);
        storage.insert(storage.end(), p, p + size);
        return 0;
    }
}

extern "C" {

    static int xer_encode_stream_callback(const void *buffer, size_t size,
            void *application_specific_key) {
        if (!application_specific_key)
            return -1;
        std::ostream &os = *reinterpret_cast<std::ostream*>(application_specific_key);
        os.write(reinterpret_cast<char const*>(buffer), size);
        return !!os ? 0 : -1;
    }


    static int xer_encode_buffer_callback(const void *buffer, size_t size,
            void *application_specific_key) {
        return encode_buffer_callback<org::sqg::supl::xer_codec>(buffer, size,
                application_specific_key);
    }

    static int uper_encode_buffer_callback(const void *buffer, size_t size,
            void *application_specific_key) {
        return encode_buffer_callback<org::sqg::supl::uper_codec>(buffer, size,
                application_specific_key);
    }

}

SUPL_SERVER_BEGIN_DECLS

bool xer_codec::encode0(::asn_TYPE_descriptor_t &td,
        void *struct_ptr,
        std::ostream &os,
        bool throwable) {
    // TODO Not implemented yet!
    std::stringstream ss;
    asn_enc_rval_t rc = ::xer_encode(&td, struct_ptr, XER_F_BASIC, &xer_encode_stream_callback, &ss);
    if (rc.encoded == -1) {
        if (throwable) {
            std::stringstream es;
            es << "xer encode failed at " << rc.failed_type->name;
            throw std::runtime_error(es.str());
        }
        return false;
    }
    return true;
}

bool xer_codec::encode0(::asn_TYPE_descriptor_t &td,
        void *struct_ptr,
        xer_codec::buffer_type &buffer,
        bool throwable) {
    std::stringstream ss;
    asn_enc_rval_t rc = ::xer_encode(&td, struct_ptr, XER_F_BASIC, &xer_encode_buffer_callback, &ss);
    if (rc.encoded == -1) {
        if (throwable) {
            std::stringstream es;
            es << "xer encode failed at " << rc.failed_type->name;
            throw std::runtime_error(es.str());
        }
        return false;
    }
    return true;
}

bool uper_codec::encode0(::asn_TYPE_descriptor_t &td,
        void *struct_ptr,
        uper_codec::buffer_type &buffer,
        bool throwable) {
    std::stringstream ss;
    asn_enc_rval_t rc = ::uper_encode(&td, struct_ptr,
            uper_encode_buffer_callback, &buffer);
    if (rc.encoded == -1) {
        if (throwable) {
            std::stringstream es;
            es << "uper encode failed at " << rc.failed_type->name;
            throw std::runtime_error(es.str());
        }
        return false;
    }
    return true;
}

SUPL_SERVER_END_DECLS
