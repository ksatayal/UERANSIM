/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NGAP-IEs"
 * 	found in "NGAP-IEs.asn"
 * 	`asn1c -pdu=all -fcompound-names -findirect-choice -fno-include-deps -no-gen-OER -gen-PER -no-gen-example -D ngap`
 */

#include "ASN_NGAP_IntersystemCellActivationRequest.h"

#include "ASN_NGAP_ProtocolExtensionContainer.h"
static int
memb_ASN_NGAP_activationID_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 16384)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_memb_ASN_NGAP_activationID_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  15,  15,  0,  16384 }	/* (0..16384,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ASN_NGAP_IntersystemCellActivationRequest_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ASN_NGAP_IntersystemCellActivationRequest, activationID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_ASN_NGAP_activationID_constr_2,  memb_ASN_NGAP_activationID_constraint_1 },
		0, 0, /* No default value */
		"activationID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ASN_NGAP_IntersystemCellActivationRequest, cellsToActivateList),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_NGAP_CellsToActivateList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellsToActivateList"
		},
	{ ATF_POINTER, 1, offsetof(struct ASN_NGAP_IntersystemCellActivationRequest, iE_Extensions),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ASN_NGAP_ProtocolExtensionContainer_174P121,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"iE-Extensions"
		},
};
static const int asn_MAP_ASN_NGAP_IntersystemCellActivationRequest_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ASN_NGAP_IntersystemCellActivationRequest_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* activationID */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* cellsToActivateList */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* iE-Extensions */
};
asn_SEQUENCE_specifics_t asn_SPC_ASN_NGAP_IntersystemCellActivationRequest_specs_1 = {
	sizeof(struct ASN_NGAP_IntersystemCellActivationRequest),
	offsetof(struct ASN_NGAP_IntersystemCellActivationRequest, _asn_ctx),
	asn_MAP_ASN_NGAP_IntersystemCellActivationRequest_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_ASN_NGAP_IntersystemCellActivationRequest_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_IntersystemCellActivationRequest = {
	"IntersystemCellActivationRequest",
	"IntersystemCellActivationRequest",
	&asn_OP_SEQUENCE,
	asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1,
	sizeof(asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1)
		/sizeof(asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1[0]), /* 1 */
	asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1,	/* Same as above */
	sizeof(asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1)
		/sizeof(asn_DEF_ASN_NGAP_IntersystemCellActivationRequest_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ASN_NGAP_IntersystemCellActivationRequest_1,
	3,	/* Elements count */
	&asn_SPC_ASN_NGAP_IntersystemCellActivationRequest_specs_1	/* Additional specs */
};

