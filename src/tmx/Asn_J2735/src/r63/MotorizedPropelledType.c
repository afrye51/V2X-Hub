/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../J2735_201603DA.ASN"
 * 	`asn1c -gen-PER -fcompound-names -fincludes-quoted -S/home/gmb/TMX-OAM/Build/asn1c/skeletons`
 */

#include "MotorizedPropelledType.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
asn_per_constraints_t asn_PER_type_MotorizedPropelledType_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  5 }	/* (0..5,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_MotorizedPropelledType_value2enum_1[] = {
	{ 0,	11,	"unavailable" },
	{ 1,	10,	"otherTypes" },
	{ 2,	10,	"wheelChair" },
	{ 3,	7,	"bicycle" },
	{ 4,	7,	"scooter" },
	{ 5,	19,	"selfBalancingDevice" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_MotorizedPropelledType_enum2value_1[] = {
	3,	/* bicycle(3) */
	1,	/* otherTypes(1) */
	4,	/* scooter(4) */
	5,	/* selfBalancingDevice(5) */
	0,	/* unavailable(0) */
	2	/* wheelChair(2) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_MotorizedPropelledType_specs_1 = {
	asn_MAP_MotorizedPropelledType_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_MotorizedPropelledType_enum2value_1,	/* N => "tag"; sorted by N */
	6,	/* Number of elements in the maps */
	7,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_MotorizedPropelledType_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_MotorizedPropelledType = {
	"MotorizedPropelledType",
	"MotorizedPropelledType",
	&asn_OP_NativeEnumerated,
	NativeEnumerated_constraint,
	asn_DEF_MotorizedPropelledType_tags_1,
	sizeof(asn_DEF_MotorizedPropelledType_tags_1)
		/sizeof(asn_DEF_MotorizedPropelledType_tags_1[0]), /* 1 */
	asn_DEF_MotorizedPropelledType_tags_1,	/* Same as above */
	sizeof(asn_DEF_MotorizedPropelledType_tags_1)
		/sizeof(asn_DEF_MotorizedPropelledType_tags_1[0]), /* 1 */
	0,	/* No OER visible constraints */
	&asn_PER_type_MotorizedPropelledType_constr_1,
	0, 0,	/* Defined elsewhere */
	&asn_SPC_MotorizedPropelledType_specs_1	/* Additional specs */
};

