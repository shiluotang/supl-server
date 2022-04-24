#ifndef SUPL_SERVER_MACROS_HPP_INCLUDED
#define SUPL_SERVER_MACROS_HPP_INCLUDED

#ifdef __cplusplus
#   define SUPL_SERVER_BEGIN_DECLS \
    namespace org { \
        namespace sqg { \
            namespace supl {

#   define SUPL_SERVER_END_DECLS \
            } \
        } \
    }
#else
#   define SUPL_SERVER_BEGIN_DECLS
#   define SUPL_SERVER_END_DECLS
#endif

#endif // SUPL_SERVER_MACROS_HPP_INCLUDED
