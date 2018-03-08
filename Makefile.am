ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS	= -g -Wall -I@top_srcdir@/src/asn1c/skeletons
AM_CFLAGS	=
AM_CXXFLAGS	=
AM_LDFLAGS	=

lib_LTLIBRARIES = \
libasn1c-skeletons.la \
libasn1c-module-supl2.la \
libsupl-server.la

libasn1c_skeletons_la_SOURCES = \
./src/asn1c/skeletons/ANY.c \
./src/asn1c/skeletons/asn_codecs_prim.c \
./src/asn1c/skeletons/asn_SEQUENCE_OF.c \
./src/asn1c/skeletons/asn_SET_OF.c \
./src/asn1c/skeletons/ber_decoder.c \
./src/asn1c/skeletons/ber_tlv_length.c \
./src/asn1c/skeletons/ber_tlv_tag.c \
./src/asn1c/skeletons/BIT_STRING.c \
./src/asn1c/skeletons/BMPString.c \
./src/asn1c/skeletons/BOOLEAN.c \
./src/asn1c/skeletons/constr_CHOICE.c \
./src/asn1c/skeletons/constr_SEQUENCE.c \
./src/asn1c/skeletons/constr_SEQUENCE_OF.c \
./src/asn1c/skeletons/constr_SET.c \
./src/asn1c/skeletons/constr_SET_OF.c \
./src/asn1c/skeletons/constr_TYPE.c \
./src/asn1c/skeletons/constraints.c \
./src/asn1c/skeletons/der_encoder.c \
./src/asn1c/skeletons/ENUMERATED.c \
./src/asn1c/skeletons/GeneralizedTime.c \
./src/asn1c/skeletons/GeneralString.c \
./src/asn1c/skeletons/GraphicString.c \
./src/asn1c/skeletons/IA5String.c \
./src/asn1c/skeletons/INTEGER.c \
./src/asn1c/skeletons/ISO646String.c \
./src/asn1c/skeletons/NativeEnumerated.c \
./src/asn1c/skeletons/NativeInteger.c \
./src/asn1c/skeletons/NativeReal.c \
./src/asn1c/skeletons/NULL.c \
./src/asn1c/skeletons/NumericString.c \
./src/asn1c/skeletons/OBJECT_IDENTIFIER.c \
./src/asn1c/skeletons/ObjectDescriptor.c \
./src/asn1c/skeletons/OCTET_STRING.c \
./src/asn1c/skeletons/per_decoder.c \
./src/asn1c/skeletons/per_encoder.c \
./src/asn1c/skeletons/per_opentype.c \
./src/asn1c/skeletons/per_support.c \
./src/asn1c/skeletons/PrintableString.c \
./src/asn1c/skeletons/REAL.c \
./src/asn1c/skeletons/RELATIVE-OID.c \
./src/asn1c/skeletons/T61String.c \
./src/asn1c/skeletons/TeletexString.c \
./src/asn1c/skeletons/UniversalString.c \
./src/asn1c/skeletons/UTCTime.c \
./src/asn1c/skeletons/UTF8String.c \
./src/asn1c/skeletons/VideotexString.c \
./src/asn1c/skeletons/VisibleString.c \
./src/asn1c/skeletons/xer_decoder.c \
./src/asn1c/skeletons/xer_encoder.c \
./src/asn1c/skeletons/xer_support.c

libasn1c_module_supl2_la_SOURCES = \
./src/asn1c/module/supl2/SUPLSTART.c
libasn1c_module_supl2_la_LIBADD = \
libasn1c-skeletons.la

libsupl_server_la_SOURCES = \
./src/supl-server.cpp
libsupl_server_la_LIBADD = \
libasn1c-skeletons.la \
libasn1c-module-supl2.la

check_PROGRAMS = test1

test1_SOURCES = ./tests/test1.cpp
test1_LDADD = \
libasn1c-skeletons.la \
libasn1c-module-supl2.la \
libsupl-server.la

TESTS = $(check_PROGRAMS)

BUILT_SOURCES = \
./src/asn1c/module/supl2/SUPLSTART.c

$(libasn1c_module_supl2_la_SOURCES): @top_srcdir@/src/asn1c/module/supl2/supl2.asn1
	rm -f ${@}
	if pushd ../src/asn1c/module/supl2 > /dev/null; then asn1c -S ../../skeletons -fcompound-names -gen-PER -pdu=auto -R supl2.asn1; popd > /dev/null; fi

