#ifndef SUPL_SERVER_UTILS_HPP_INCLUDED
#define SUPL_SERVER_UTILS_HPP_INCLUDED

#include <ios>
#include <locale>
#include <vector>
#include <algorithm>

#include "../macros.hpp"

SUPL_SERVER_BEGIN_DECLS

template <typename CharT, typename Traits = std::char_traits<CharT> >
struct basic_ios_guarder {
    typedef typename std::basic_ios<CharT, Traits> xios;
    typedef typename xios::char_type char_type;
    typedef typename xios::fmtflags fmtflags;
    typedef std::streamsize streamsize;

    basic_ios_guarder(xios &stream)
        : _M_stream(stream)
        , _M_flags(stream.flags())
        , _M_precision(stream.precision())
        , _M_width(stream.width())
        , _M_fillchar(stream.fill())
        , _M_locale(stream.getloc())
    {
    }

    virtual ~basic_ios_guarder() {
        _M_stream.flags(_M_flags);
        _M_stream.precision(_M_precision);
        _M_stream.width(_M_width);
        _M_stream.fill(_M_fillchar);
        _M_stream.imbue(_M_locale);
    }

    xios        &_M_stream;
    fmtflags    _M_flags;
    streamsize  _M_precision;
    streamsize  _M_width;
    char_type   _M_fillchar;
    std::locale _M_locale;
};

typedef basic_ios_guarder<char> ios_guarder;
typedef basic_ios_guarder<wchar_t> wios_guarder;

SUPL_SERVER_END_DECLS


#endif // SUPL_SERVER_UTILS_HPP_INCLUDED
