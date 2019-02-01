/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "../J2735_201603DA.ASN"
 * 	`asn1c -gen-PER -fcompound-names -fincludes-quoted -S/home/gmb/TMX-OAM/Build/asn1c/skeletons`
 */

#include "NodeOffsetPointLL.h"

asn_per_constraints_t asn_PER_type_NodeOffsetPointLL_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  7 }	/* (0..7) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_NodeOffsetPointLL_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL1),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_24B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL2),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_28B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL3),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_32B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL3"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL4),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_36B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL5),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_44B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LL6),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LL_48B,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LL6"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.node_LatLon),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Node_LLmD_64b,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"node-LatLon"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NodeOffsetPointLL, choice.regional),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RegionalExtension_124P0,
		0,
		0,	/* Defer constraints checking to the member type */
		0,	/* OER is not compiled, use -gen-OER */
		0,	/* No PER visible constraints */
		0,
		"regional"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_NodeOffsetPointLL_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* node-LL1 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* node-LL2 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* node-LL3 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* node-LL4 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* node-LL5 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* node-LL6 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* node-LatLon */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* regional */
};
asn_CHOICE_specifics_t asn_SPC_NodeOffsetPointLL_specs_1 = {
	sizeof(struct NodeOffsetPointLL),
	offsetof(struct NodeOffsetPointLL, _asn_ctx),
	offsetof(struct NodeOffsetPointLL, present),
	sizeof(((struct NodeOffsetPointLL *)0)->present),
	asn_MAP_NodeOffsetPointLL_tag2el_1,
	8,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_NodeOffsetPointLL = {
	"NodeOffsetPointLL",
	"NodeOffsetPointLL",
	&asn_OP_CHOICE,
	CHOICE_constraint,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No OER visible constraints */
	&asn_PER_type_NodeOffsetPointLL_constr_1,
	asn_MBR_NodeOffsetPointLL_1,
	8,	/* Elements count */
	&asn_SPC_NodeOffsetPointLL_specs_1	/* Additional specs */
};

