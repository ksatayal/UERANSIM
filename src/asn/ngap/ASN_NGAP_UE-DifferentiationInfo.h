/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NGAP-IEs"
 * 	found in "NGAP-IEs.asn"
 * 	`asn1c -pdu=all -fcompound-names -findirect-choice -fno-include-deps -no-gen-OER -gen-PER -no-gen-example -D ngap`
 */

#ifndef	_ASN_NGAP_UE_DifferentiationInfo_H_
#define	_ASN_NGAP_UE_DifferentiationInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ASN_NGAP_UE_DifferentiationInfo__periodicCommunicationIndicator {
	ASN_NGAP_UE_DifferentiationInfo__periodicCommunicationIndicator_periodically	= 0,
	ASN_NGAP_UE_DifferentiationInfo__periodicCommunicationIndicator_ondemand	= 1
	/*
	 * Enumeration is extensible
	 */
} e_ASN_NGAP_UE_DifferentiationInfo__periodicCommunicationIndicator;
typedef enum ASN_NGAP_UE_DifferentiationInfo__stationaryIndication {
	ASN_NGAP_UE_DifferentiationInfo__stationaryIndication_stationary	= 0,
	ASN_NGAP_UE_DifferentiationInfo__stationaryIndication_mobile	= 1
	/*
	 * Enumeration is extensible
	 */
} e_ASN_NGAP_UE_DifferentiationInfo__stationaryIndication;
typedef enum ASN_NGAP_UE_DifferentiationInfo__trafficProfile {
	ASN_NGAP_UE_DifferentiationInfo__trafficProfile_single_packet	= 0,
	ASN_NGAP_UE_DifferentiationInfo__trafficProfile_dual_packets	= 1,
	ASN_NGAP_UE_DifferentiationInfo__trafficProfile_multiple_packets	= 2
	/*
	 * Enumeration is extensible
	 */
} e_ASN_NGAP_UE_DifferentiationInfo__trafficProfile;
typedef enum ASN_NGAP_UE_DifferentiationInfo__batteryIndication {
	ASN_NGAP_UE_DifferentiationInfo__batteryIndication_battery_powered	= 0,
	ASN_NGAP_UE_DifferentiationInfo__batteryIndication_battery_powered_not_rechargeable_or_replaceable	= 1,
	ASN_NGAP_UE_DifferentiationInfo__batteryIndication_not_battery_powered	= 2
	/*
	 * Enumeration is extensible
	 */
} e_ASN_NGAP_UE_DifferentiationInfo__batteryIndication;

/* Forward declarations */
struct ASN_NGAP_ScheduledCommunicationTime;
struct ASN_NGAP_ProtocolExtensionContainer;

/* ASN_NGAP_UE-DifferentiationInfo */
typedef struct ASN_NGAP_UE_DifferentiationInfo {
	long	*periodicCommunicationIndicator;	/* OPTIONAL */
	long	*periodicTime;	/* OPTIONAL */
	struct ASN_NGAP_ScheduledCommunicationTime	*scheduledCommunicationTime;	/* OPTIONAL */
	long	*stationaryIndication;	/* OPTIONAL */
	long	*trafficProfile;	/* OPTIONAL */
	long	*batteryIndication;	/* OPTIONAL */
	struct ASN_NGAP_ProtocolExtensionContainer	*iE_Extensions;	/* OPTIONAL */
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ASN_NGAP_UE_DifferentiationInfo_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_periodicCommunicationIndicator_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_stationaryIndication_8;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_trafficProfile_12;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_batteryIndication_17;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_ASN_NGAP_UE_DifferentiationInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_ASN_NGAP_UE_DifferentiationInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_ASN_NGAP_UE_DifferentiationInfo_1[7];

#ifdef __cplusplus
}
#endif

#endif	/* _ASN_NGAP_UE_DifferentiationInfo_H_ */
#include <asn_internal.h>
