/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "Test"
 * 	found in "test.asn1"
 * 	`asn1c -S ../../skeletons -fcompound-names -gen-PER -pdu=auto`
 */

#ifndef	_ITag_H_
#define	_ITag_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HTag.h"
#include "GTag.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ITag */
typedef struct ITag {
	HTag_t	 test;
	GTag_t	 test2;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ITag_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ITag;

#ifdef __cplusplus
}
#endif

#endif	/* _ITag_H_ */
#include <asn_internal.h>
