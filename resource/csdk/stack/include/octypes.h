//******************************************************************
//
// Copyright 2014 Intel Mobile Communications GmbH All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//******************************************************************


/**
 * @file
 *
 * This file contains the definition, types and APIs for resource(s) be implemented.
 */

#ifndef OCTYPES_H_
#define OCTYPES_H_

#include "platform_features.h"
#include "ocstackconfig.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
#include <string.h>

extern "C" {
#endif // __cplusplus

/** For the feature presence.*/
#define WITH_PRESENCE

#include "ocpresence.h"
//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

/**
 * OIC Virtual resources supported by every OIC device.
 */
/**
 *  Default discovery mechanism using '/oic/res' is supported by all OIC devices
 *  That are Discoverable.
 */
#define OC_RSRVD_WELL_KNOWN_URI               "/oic/res"

/** Device URI.*/
#define OC_RSRVD_DEVICE_URI                   "/oic/d"

/** Platform URI.*/
#define OC_RSRVD_PLATFORM_URI                 "/oic/p"

/** Resource Type.*/
#define OC_RSRVD_RESOURCE_TYPES_URI           "/oic/res/types/d"
#if defined (ROUTING_GATEWAY) || defined (ROUTING_EP)
/** Gateway URI.*/
#define OC_RSRVD_GATEWAY_URI                  "/oic/gateway"
#endif
#ifdef WITH_PRESENCE

/** Presence URI through which the OIC devices advertise their presence.*/
#define OC_RSRVD_PRESENCE_URI                 "/oic/ad"

/** Sets the default time to live (TTL) for presence.*/
#define OC_DEFAULT_PRESENCE_TTL_SECONDS (60)

/** For multicast Discovery mechanism.*/
#define OC_MULTICAST_DISCOVERY_URI           "/oic/res"

/** Separator for multiple query string.*/
#define OC_QUERY_SEPARATOR                "&;"

/**
 *  OC_DEFAULT_PRESENCE_TTL_SECONDS sets the default time to live (TTL) for presence.
 */
#define OC_DEFAULT_PRESENCE_TTL_SECONDS (60)

/**
 *  OC_MAX_PRESENCE_TTL_SECONDS sets the maximum time to live (TTL) for presence.
 *  NOTE: Changing the setting to a longer duration may lead to unsupported and untested
 *  operation.
 *  60 sec/min * 60 min/hr * 24 hr/day
 */
#define OC_MAX_PRESENCE_TTL_SECONDS     (60 * 60 * 24)
#endif

/**
 *  Presence "Announcement Triggers".
 */

/** To create.*/
#define OC_RSRVD_TRIGGER_CREATE         "create"

/** To change.*/
#define OC_RSRVD_TRIGGER_CHANGE         "change"

/** To delete.*/
#define OC_RSRVD_TRIGGER_DELETE         "delete"

/**
 *  Attributes used to form a proper OIC conforming JSON message.
 */

#define OC_RSRVD_OC                     "oic"

/** For payload. */

#define OC_RSRVD_PAYLOAD                "payload"

/** To represent href */
#define OC_RSRVD_HREF                   "href"

/** To represent property*/
#define OC_RSRVD_PROPERTY               "prop"

/** For representation.*/
#define OC_RSRVD_REPRESENTATION         "rep"

/** To represent content type.*/
#define OC_RSRVD_CONTENT_TYPE           "ct"

/** To represent resource type.*/
#define OC_RSRVD_RESOURCE_TYPE          "rt"

/** To represent resource type with presence.*/
#define OC_RSRVD_RESOURCE_TYPE_PRESENCE "oic.wk.ad"

/** To represent resource type with device.*/
#define OC_RSRVD_RESOURCE_TYPE_DEVICE   "oic.wk.d"

/** To represent resource type with platform.*/
#define OC_RSRVD_RESOURCE_TYPE_PLATFORM "oic.wk.p"

/** To represent resource type with RES.*/
#define OC_RSRVD_RESOURCE_TYPE_RES    "oic.wk.res"

/** To represent interface.*/
#define OC_RSRVD_INTERFACE              "if"

/** To represent time to live.*/
#define OC_RSRVD_TTL                    "ttl"

/** To represent non*/
#define OC_RSRVD_NONCE                  "non"

/** To represent trigger type.*/
#define OC_RSRVD_TRIGGER                "trg"

/** To represent links.*/
#define OC_RSRVD_LINKS                  "links"

/** To represent default interface.*/
#define OC_RSRVD_INTERFACE_DEFAULT      "oic.if.baseline"

/** To represent read-only interface.*/
#define OC_RSRVD_INTERFACE_READ         "oic.if.r"

/** To represent ll interface.*/
#define OC_RSRVD_INTERFACE_LL           "oic.if.ll"

/** To represent batch interface.*/
#define OC_RSRVD_INTERFACE_BATCH        "oic.if.b"

/** To represent interface group.*/
#define OC_RSRVD_INTERFACE_GROUP        "oic.mi.grp"

/** To represent MFG date.*/
#define OC_RSRVD_MFG_DATE               "mndt"

/** To represent FW version.*/
#define OC_RSRVD_FW_VERSION             "mnfv"

/** To represent host name.*/
#define OC_RSRVD_HOST_NAME              "hn"

/** To represent policy.*/
#define OC_RSRVD_POLICY                 "p"

/** To represent bitmap.*/
#define OC_RSRVD_BITMAP                 "bm"

/** For security.*/
#define OC_RSRVD_SECURE                 "sec"

/** Port. */
#define OC_RSRVD_HOSTING_PORT           "port"

/** TCP Port. */
#define OC_RSRVD_TCP_PORT               "tcp"

/** For Server instance ID.*/
#define OC_RSRVD_SERVER_INSTANCE_ID     "sid"

/**
 *  Platform.
 */

/** Platform ID. */
#define OC_RSRVD_PLATFORM_ID            "pi"

/** Platform MFG NAME. */
#define OC_RSRVD_MFG_NAME               "mnmn"

/** Platform URL. */
#define OC_RSRVD_MFG_URL                "mnml"

/** Model Number.*/
#define OC_RSRVD_MODEL_NUM              "mnmo"

/** Platform MFG Date.*/
#define OC_RSRVD_MFG_DATE               "mndt"

/** Platform versio.n */
#define OC_RSRVD_PLATFORM_VERSION       "mnpv"

/** Platform Operating system version. */
#define OC_RSRVD_OS_VERSION             "mnos"

/** Platform Hardware version. */
#define OC_RSRVD_HARDWARE_VERSION       "mnhw"

/**Platform Firmware version. */
#define OC_RSRVD_FIRMWARE_VERSION       "mnfv"

/** Support URL for the platform. */
#define OC_RSRVD_SUPPORT_URL            "mnsl"

/** System time for the platform. */
#define OC_RSRVD_SYSTEM_TIME             "st"

/**
 *  Device.
 */

/** Device ID.*/
#define OC_RSRVD_DEVICE_ID              "di"

/** Device Name.*/
#define OC_RSRVD_DEVICE_NAME            "n"

/** Device specification version.*/
#define OC_RSRVD_SPEC_VERSION           "icv"

/** Device data model.*/
#define OC_RSRVD_DATA_MODEL_VERSION     "dmv"

/** Device specification version.*/
#define OC_SPEC_VERSION                "core.1.0.0"

/** Device Data Model version.*/
#define OC_DATA_MODEL_VERSION          "res.1.0.0"

/**
 *  These provide backward compatibility - their use is deprecated.
 */
#ifndef GOING_AWAY

/** Multicast Prefix.*/
#define OC_MULTICAST_PREFIX                  "224.0.1.187:5683"

/** Multicast IP address.*/
#define OC_MULTICAST_IP                      "224.0.1.187"

/** Multicast Port.*/
#define OC_MULTICAST_PORT                    5683
#endif // GOING_AWAY

/** Max Device address size. */
#ifdef RA_ADAPTER
#define MAX_ADDR_STR_SIZE (256)
#else
/** Max Address could be
 * "coap+tcp://[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:yyy.yyy.yyy.yyy]:xxxxx"
 * +1 for null terminator.
 */
#define MAX_ADDR_STR_SIZE (65)
#endif

/** Length of MAC address */
#define MAC_ADDR_STR_SIZE (17)

/** Blocks of MAC address */
#define MAC_ADDR_BLOCKS (6)

/** Max identity size. */
#define MAX_IDENTITY_SIZE (32)

/** Universal unique identity size. */
#define UUID_IDENTITY_SIZE (128/8)

/** Resource Directory */

/** Resource Directory URI used to Discover RD and Publish resources.*/
#define OC_RSRVD_RD_URI                  "/oic/rd"

/** To represent resource type with rd.*/
#define OC_RSRVD_RESOURCE_TYPE_RD        "oic.wk.rd"

/** RD Discovery bias factor type. */
#define OC_RSRVD_RD_DISCOVERY_SEL        "sel"

/** Base URI. */
#define OC_RSRVD_BASE_URI                "baseURI"

/** Unique value per collection/link. */
#define OC_RSRVD_INS                     "ins"

/** Allowable resource types in the links. */
#define OC_RSRVD_RTS                     "rts"

/** Default relationship. */
#define OC_RSRVD_DREL                    "drel"

/** Defines relationship between links. */
#define OC_RSRVD_REL                     "rel"

/** Defines title. */
#define OC_RSRVD_TITLE                   "title"

/** Defines URI. */
#define OC_RSRVD_URI                     "uri"

/** Defines media type. */
#define OC_RSRVD_MEDIA_TYPE              "mt"

/** To represent resource type with Publish RD.*/
#define OC_RSRVD_RESOURCE_TYPE_RDPUBLISH "oic.wk.rdpub"

/** Cloud Account */

/** Account URI.*/
#define OC_RSRVD_ACCOUNT_URI               "/.well-known/ocf/account"

/** Account session URI.*/
#define OC_RSRVD_ACCOUNT_SESSION_URI       "/.well-known/ocf/account/session"

/** Account token refresh URI.*/
#define OC_RSRVD_ACCOUNT_TOKEN_REFRESH_URI "/.well-known/ocf/account/tokenrefresh"

/** Defines auth provider. */
#define OC_RSRVD_AUTHPROVIDER              "authprovider"

/** Defines auth code. */
#define OC_RSRVD_AUTHCODE                  "authcode"

/** Defines session. */
#define OC_RSRVD_ACCESS_TOKEN              "accesstoken"

/** Defines status. */
#define OC_RSRVD_STATUS                    "status"

/** Defines grant type. */
#define OC_RSRVD_GRANT_TYPE                "granttype"

/** Defines refresh token. */
#define OC_RSRVD_REFRESH_TOKEN             "refreshtoken"

/** To represent grant type with refresh token. */
#define OC_RSRVD_GRANT_TYPE_REFRESH_TOKEN  "refresh_token"

/**
 * Mark a parameter as unused. Used to prevent unused variable compiler warnings.
 * Used in three cases:
 * 1. in callbacks when one of the parameters are unused
 * 2. when due to code changes a functions parameter is no longer
 *    used but must be left in place for backward compatibility
 *    reasons.
 * 3. a variable is only used in the debug build variant and would
 *    give a build warning in release mode.
 */
#define OC_UNUSED(x) (void)(x)

/**
 * These enums (OCTransportAdapter and OCTransportFlags) must
 * be kept synchronized with OCConnectivityType (below) as well as
 * CATransportAdapter and CATransportFlags (in CACommon.h).
 */
typedef enum
{
    /** value zero indicates discovery.*/
    OC_DEFAULT_ADAPTER = 0,

    /** IPv4 and IPv6, including 6LoWPAN.*/
    OC_ADAPTER_IP           = (1 << 0),

    /** GATT over Bluetooth LE.*/
    OC_ADAPTER_GATT_BTLE    = (1 << 1),

    /** RFCOMM over Bluetooth EDR.*/
    OC_ADAPTER_RFCOMM_BTEDR = (1 << 2),
#ifdef RA_ADAPTER
    /**Remote Access over XMPP.*/
    OC_ADAPTER_REMOTE_ACCESS = (1 << 3),
#endif
    /** CoAP over TCP.*/
    OC_ADAPTER_TCP           = (1 << 4),

    /** NFC Transport for Messaging.*/
    OC_ADAPTER_NFC           = (1 << 5)
} OCTransportAdapter;

/**
 *  Enum layout assumes some targets have 16-bit integer (e.g., Arduino).
 */
typedef enum
{
    /** default flag is 0*/
    OC_DEFAULT_FLAGS = 0,

    /** Insecure transport is the default (subject to change).*/
    /** secure the transport path*/
    OC_FLAG_SECURE     = (1 << 4),

    /** IPv4 & IPv6 auto-selection is the default.*/
    /** IP & TCP adapter only.*/
    OC_IP_USE_V6       = (1 << 5),

    /** IP & TCP adapter only.*/
    OC_IP_USE_V4       = (1 << 6),

    /** Multicast only.*/
    OC_MULTICAST       = (1 << 7),

    /** Link-Local multicast is the default multicast scope for IPv6.
     *  These are placed here to correspond to the IPv6 multicast address bits.*/

    /** IPv6 Interface-Local scope (loopback).*/
    OC_SCOPE_INTERFACE = 0x1,

    /** IPv6 Link-Local scope (default).*/
    OC_SCOPE_LINK      = 0x2,

    /** IPv6 Realm-Local scope. */
    OC_SCOPE_REALM     = 0x3,

    /** IPv6 Admin-Local scope. */
    OC_SCOPE_ADMIN     = 0x4,

    /** IPv6 Site-Local scope. */
    OC_SCOPE_SITE      = 0x5,

    /** IPv6 Organization-Local scope. */
    OC_SCOPE_ORG       = 0x8,

    /**IPv6 Global scope. */
    OC_SCOPE_GLOBAL    = 0xE,

} OCTransportFlags;

/** Bit mask for scope.*/
#define OC_MASK_SCOPE    (0x000F)

/** Bit mask for Mods.*/
#define OC_MASK_MODS     (0x0FF0)
#define OC_MASK_FAMS     (OC_IP_USE_V6|OC_IP_USE_V4)

typedef struct OCStringLL
{
    struct OCStringLL *next;
    char* value;
} OCStringLL;

/**
 * End point identity.
 */
typedef struct
{
    /** Identity Length */
    uint16_t id_length;

    /** Array of end point identity.*/
    unsigned char id[MAX_IDENTITY_SIZE];
} OCIdentity;

/**
 * Universally unique identifier.
 */
typedef struct
{
    /** identitifier string.*/
    unsigned char id[UUID_IDENTITY_SIZE];
} OCUUIdentity;

/**
 * Data structure to encapsulate IPv4/IPv6/Contiki/lwIP device addresses.
 * OCDevAddr must be the same as CAEndpoint (in CACommon.h).
 */
typedef struct
{
    /** adapter type.*/
    OCTransportAdapter      adapter;

    /** transport modifiers.*/
    OCTransportFlags        flags;

    /** for IP.*/
    uint16_t                port;

    /** address for all adapters.*/
    char                    addr[MAX_ADDR_STR_SIZE];

    /** usually zero for default interface.*/
    uint32_t                ifindex;
#if defined (ROUTING_GATEWAY) || defined (ROUTING_EP)
    char                    routeData[MAX_ADDR_STR_SIZE]; //destination GatewayID:ClientId
#endif
} OCDevAddr;

/**
 * This enum type includes elements of both ::OCTransportAdapter and ::OCTransportFlags.
 * It is defined conditionally because the smaller definition limits expandability on 32/64 bit
 * integer machines, and the larger definition won't fit into an enum on 16-bit integer machines
 * like Arduino.
 *
 * This structure must directly correspond to ::OCTransportAdapter and ::OCTransportFlags.
 */
typedef enum
{
    /** use when defaults are ok. */
    CT_DEFAULT = 0,

    /** IPv4 and IPv6, including 6LoWPAN.*/
    CT_ADAPTER_IP           = (1 << 16),

    /** GATT over Bluetooth LE.*/
    CT_ADAPTER_GATT_BTLE    = (1 << 17),

    /** RFCOMM over Bluetooth EDR.*/
    CT_ADAPTER_RFCOMM_BTEDR = (1 << 18),

#ifdef RA_ADAPTER
    /** Remote Access over XMPP.*/
    CT_ADAPTER_REMOTE_ACCESS = (1 << 19),
#endif
    /** CoAP over TCP.*/
    CT_ADAPTER_TCP     = (1 << 20),

    /** NFC Transport.*/
    CT_ADAPTER_NFC     = (1 << 21),

    /** Insecure transport is the default (subject to change).*/

    /** secure the transport path.*/
    CT_FLAG_SECURE     = (1 << 4),

    /** IPv4 & IPv6 autoselection is the default.*/

    /** IP adapter only.*/
    CT_IP_USE_V6       = (1 << 5),

    /** IP adapter only.*/
    CT_IP_USE_V4       = (1 << 6),

    /** Link-Local multicast is the default multicast scope for IPv6.
     * These are placed here to correspond to the IPv6 address bits.*/

    /** IPv6 Interface-Local scope(loopback).*/
    CT_SCOPE_INTERFACE = 0x1,

    /** IPv6 Link-Local scope (default).*/
    CT_SCOPE_LINK      = 0x2,

    /** IPv6 Realm-Local scope.*/
    CT_SCOPE_REALM     = 0x3,

    /** IPv6 Admin-Local scope.*/
    CT_SCOPE_ADMIN     = 0x4,

    /** IPv6 Site-Local scope.*/
    CT_SCOPE_SITE      = 0x5,

    /** IPv6 Organization-Local scope.*/
    CT_SCOPE_ORG       = 0x8,

    /** IPv6 Global scope.*/
    CT_SCOPE_GLOBAL    = 0xE,
} OCConnectivityType;

/** bit shift required for connectivity adapter.*/
#define CT_ADAPTER_SHIFT 16

/** Mask Flag.*/
#define CT_MASK_FLAGS 0xFFFF

/** Mask Adapter.*/
#define CT_MASK_ADAPTER 0xFFFF0000

/**
 *  OCDoResource methods to dispatch the request
 */
typedef enum
{
    OC_REST_NOMETHOD       = 0,

    /** Read.*/
    OC_REST_GET            = (1 << 0),

    /** Write.*/
    OC_REST_PUT            = (1 << 1),

    /** Update.*/
    OC_REST_POST           = (1 << 2),

    /** Delete.*/
    OC_REST_DELETE         = (1 << 3),

    /** Register observe request for most up date notifications ONLY.*/
    OC_REST_OBSERVE        = (1 << 4),

    /** Register observe request for all notifications, including stale notifications.*/
    OC_REST_OBSERVE_ALL    = (1 << 5),

    /** De-register observation, intended for internal use.*/
    OC_REST_CANCEL_OBSERVE = (1 << 6),

#ifdef WITH_PRESENCE
    /** Subscribe for all presence notifications of a particular resource.*/
    OC_REST_PRESENCE       = (1 << 7),

#endif
    /** Allows OCDoResource caller to do discovery.*/
    OC_REST_DISCOVER       = (1 << 8)
} OCMethod;

/**
 *  Formats for payload encoding.
 */
typedef enum
{
    OC_FORMAT_CBOR,
    OC_FORMAT_UNDEFINED,
    OC_FORMAT_UNSUPPORTED,
} OCPayloadFormat;

/**
 * Host Mode of Operation.
 */
typedef enum
{
    OC_CLIENT = 0,
    OC_SERVER,
    OC_CLIENT_SERVER,
    OC_GATEWAY          /**< Client server mode along with routing capabilities.*/
} OCMode;

/**
 * Quality of Service attempts to abstract the guarantees provided by the underlying transport
 * protocol. The precise definitions of each quality of service level depend on the
 * implementation. In descriptions below are for the current implementation and may changed
 * over time.
 */
typedef enum
{
    /** Packet delivery is best effort.*/
    OC_LOW_QOS = 0,

    /** Packet delivery is best effort.*/
    OC_MEDIUM_QOS,

    /** Acknowledgments are used to confirm delivery.*/
    OC_HIGH_QOS,

    /** No Quality is defined, let the stack decide.*/
    OC_NA_QOS
} OCQualityOfService;

/**
 * Resource Properties.
 * The value of a policy property is defined as bitmap.
 * The LSB represents OC_DISCOVERABLE and Second LSB bit represents OC_OBSERVABLE and so on.
 * Not including the policy property is equivalent to zero.
 *
 */
typedef enum
{
    /** When none of the bits are set, the resource is non-discoverable &
     *  non-observable by the client.*/
    OC_RES_PROP_NONE = (0),

    /** When this bit is set, the resource is allowed to be discovered by clients.*/
    OC_DISCOVERABLE  = (1 << 0),

    /** When this bit is set, the resource is allowed to be observed by clients.*/
    OC_OBSERVABLE    = (1 << 1),

    /** When this bit is set, the resource is initialized, otherwise the resource
     *  is 'inactive'. 'inactive' signifies that the resource has been marked for
     *  deletion or is already deleted.*/
    OC_ACTIVE        = (1 << 2),

    /** When this bit is set, the resource has been marked as 'slow'.
     * 'slow' signifies that responses from this resource can expect delays in
     *  processing its requests from clients.*/
    OC_SLOW          = (1 << 3),

#ifdef __WITH_DTLS__
    /** When this bit is set, the resource is a secure resource.*/
    OC_SECURE        = (1 << 4),
#else
    OC_SECURE        = (0),
#endif

    /** When this bit is set, the resource is allowed to be discovered only
     *  if discovery request contains an explicit querystring.
     *  Ex: GET /oic/res?rt=oic.sec.acl */
    OC_EXPLICIT_DISCOVERABLE   = (1 << 5),

#ifdef WITH_MQ
    /** When this bit is set, the resource is allowed to be published */
    OC_MQ_PUBLISHER     = (1 << 6),
#endif

#ifdef MQ_BROKER
    /** When this bit is set, the resource is allowed to be notified as MQ broker.*/
    OC_MQ_BROKER        = (1 << 7),
#endif
} OCResourceProperty;

/**
 * Transport Protocol IDs.
 */
typedef enum
{
    /** For invalid ID.*/
    OC_INVALID_ID   = (1 << 0),

    /* For coap ID.*/
    OC_COAP_ID      = (1 << 1)
} OCTransportProtocolID;

/**
 * Declares Stack Results & Errors.
 */
typedef enum
{
    /** Success status code - START HERE.*/
    OC_STACK_OK = 0,
    OC_STACK_RESOURCE_CREATED,
    OC_STACK_RESOURCE_DELETED,
    OC_STACK_CONTINUE,
    OC_STACK_RESOURCE_CHANGED,
    /** Success status code - END HERE.*/

    /** Error status code - START HERE.*/
    OC_STACK_INVALID_URI = 20,
    OC_STACK_INVALID_QUERY,
    OC_STACK_INVALID_IP,
    OC_STACK_INVALID_PORT,
    OC_STACK_INVALID_CALLBACK,
    OC_STACK_INVALID_METHOD,

    /** Invalid parameter.*/
    OC_STACK_INVALID_PARAM,
    OC_STACK_INVALID_OBSERVE_PARAM,
    OC_STACK_NO_MEMORY,
    OC_STACK_COMM_ERROR,
    OC_STACK_TIMEOUT,
    OC_STACK_ADAPTER_NOT_ENABLED,
    OC_STACK_NOTIMPL,

    /** Resource not found.*/
    OC_STACK_NO_RESOURCE,

    /** e.g: not supported method or interface.*/
    OC_STACK_RESOURCE_ERROR,
    OC_STACK_SLOW_RESOURCE,
    OC_STACK_DUPLICATE_REQUEST,

    /** Resource has no registered observers.*/
    OC_STACK_NO_OBSERVERS,
    OC_STACK_OBSERVER_NOT_FOUND,
    OC_STACK_VIRTUAL_DO_NOT_HANDLE,
    OC_STACK_INVALID_OPTION,

    /** The remote reply contained malformed data.*/
    OC_STACK_MALFORMED_RESPONSE,
    OC_STACK_PERSISTENT_BUFFER_REQUIRED,
    OC_STACK_INVALID_REQUEST_HANDLE,
    OC_STACK_INVALID_DEVICE_INFO,
    OC_STACK_INVALID_JSON,

    /** Request is not authorized by Resource Server. */
    OC_STACK_UNAUTHORIZED_REQ,
    OC_STACK_TOO_LARGE_REQ,

    /** Error code from PDM */
    OC_STACK_PDM_IS_NOT_INITIALIZED,
    OC_STACK_DUPLICATE_UUID,
    OC_STACK_INCONSISTENT_DB,

    /**
     * Error code from OTM
     * This error is pushed from DTLS interface when handshake failure happens
     */
    OC_STACK_AUTHENTICATION_FAILURE,

    /** Insert all new error codes here!.*/
#ifdef WITH_PRESENCE
    OC_STACK_PRESENCE_STOPPED = 128,
    OC_STACK_PRESENCE_TIMEOUT,
    OC_STACK_PRESENCE_DO_NOT_HANDLE,
#endif
    /** ERROR in stack.*/
    OC_STACK_ERROR = 255
    /** Error status code - END HERE.*/
} OCStackResult;

/**
 * Handle to an OCDoResource invocation.
 */
typedef void * OCDoHandle;

/**
 * Handle to an OCResource object owned by the OCStack.
 */
typedef void * OCResourceHandle;

/**
 * Handle to an OCRequest object owned by the OCStack.
 */
typedef void * OCRequestHandle;

/**
 * Unique identifier for each observation request. Used when observations are
 * registered or de-registered. Used by entity handler to signal specific
 * observers to be notified of resource changes.
 * There can be maximum of 256 observations per server.
 */
typedef uint8_t OCObservationId;

/**
 * Action associated with observation.
 */
typedef enum
{
    /** To Register. */
    OC_OBSERVE_REGISTER = 0,

    /** To Deregister. */
    OC_OBSERVE_DEREGISTER = 1,

    /** Others. */
    OC_OBSERVE_NO_OPTION = 2
} OCObserveAction;


/**
 * Persistent storage handlers. An APP must provide OCPersistentStorage handler pointers
 * when it calls OCRegisterPersistentStorageHandler.
 * Persistent storage open handler points to default file path.
 * It should check file path and whether the file is symbolic link or no.
 * Application can point to appropriate SVR database path for it's IoTivity Server.
 */
typedef struct {
    /** Persistent storage file path.*/
    FILE* (* open)(const char *path, const char *mode);

    /** Persistent storage read handler.*/
    size_t (* read)(void *ptr, size_t size, size_t nmemb, FILE *stream);

    /** Persistent storage write handler.*/
    size_t (* write)(const void *ptr, size_t size, size_t nmemb, FILE *stream);

    /** Persistent storage close handler.*/
    int (* close)(FILE *fp);

    /** Persistent storage unlink handler.*/
    int (* unlink)(const char *path);
} OCPersistentStorage;

/**
 * Possible returned values from entity handler.
 */
typedef struct
{
    /** Action associated with observation request.*/
    OCObserveAction action;

    /** Identifier for observation being registered/deregistered.*/
    OCObservationId obsId;
} OCObservationInfo;

/**
 * Possible returned values from entity handler.
 */
typedef enum
{
    OC_EH_OK = 0,
    OC_EH_ERROR,
    OC_EH_RESOURCE_CREATED, // 2.01
    OC_EH_RESOURCE_DELETED, // 2.02
    OC_EH_SLOW, // 2.05
    OC_EH_FORBIDDEN, // 4.03
    OC_EH_RESOURCE_NOT_FOUND, // 4.04
    OC_EH_VALID,   // 2.03
    OC_EH_CHANGED, // 2.04
    OC_EH_CONTENT, // 2.05
    OC_EH_BAD_REQ, // 4.00
    OC_EH_UNAUTHORIZED_REQ, // 4.01
    OC_EH_BAD_OPT, // 4.02
    OC_EH_METHOD_NOT_ALLOWED, // 4.05
    OC_EH_NOT_ACCEPTABLE, // 4.06
    OC_EH_INTERNAL_SERVER_ERROR, // 5.00
    OC_EH_RETRANSMIT_TIMEOUT // 5.04
} OCEntityHandlerResult;

/**
 * This structure will be used to define the vendor specific header options to be included
 * in communication packets.
 */
typedef struct OCHeaderOption
{
    /** The protocol ID this option applies to.*/
    OCTransportProtocolID protocolID;

    /** The header option ID which will be added to communication packets.*/
    uint16_t optionID;

    /** its length 191.*/
    uint16_t optionLength;

    /** pointer to its data.*/
    uint8_t optionData[MAX_HEADER_OPTION_DATA_LENGTH];

#ifdef SUPPORTS_DEFAULT_CTOR
    OCHeaderOption() = default;
    OCHeaderOption(OCTransportProtocolID pid,
                   uint16_t optId,
                   uint16_t optlen,
                   const uint8_t* optData)
        : protocolID(pid),
          optionID(optId),
          optionLength(optlen)
    {

        // parameter includes the null terminator.
        optionLength = optionLength < MAX_HEADER_OPTION_DATA_LENGTH ?
                        optionLength : MAX_HEADER_OPTION_DATA_LENGTH;
        memcpy(optionData, optData, optionLength);
        optionData[optionLength - 1] = '\0';
    }
#endif
} OCHeaderOption;


/**
 * This structure describes the platform properties. All non-Null properties will be
 * included in a platform discovery request.
 */
typedef struct
{
    /** Platform ID.*/
    char *platformID;

    /** Manufacturer name.*/
    char *manufacturerName;

    /** Manufacturer URL for platform property.*/
    char *manufacturerUrl;

    /** Model number.*/
    char *modelNumber;

    /** Manufacturer date.*/
    char *dateOfManufacture;

    /** Platform version.*/
    char *platformVersion;

    /** Operating system version.*/
    char *operatingSystemVersion;

    /** HW version.*/
    char *hardwareVersion;

    /** FW version.*/
    char *firmwareVersion;

    /** Platform support URL.*/
    char *supportUrl;

    /** System time.*/
    char *systemTime;

} OCPlatformInfo;

/**
 * This structure is expected as input for device properties.
 * device name is mandatory and expected from the application.
 * device id of type UUID will be generated by the stack.
 */
typedef struct
{
    /** Pointer to the device name.*/
    char *deviceName;
    /** Pointer to the types.*/
    OCStringLL *types;
    /** Pointer to the device specification version.*/
    char *specVersion;
    /** Pointer to the device data model versions (in CSV format).*/
    OCStringLL *dataModelVersions;
} OCDeviceInfo;

#ifdef RA_ADAPTER
/**
 * callback for bound JID
 */
typedef void (*jid_bound_cb)(char *jid);

/**
 * CA Remote Access information for XMPP Client
 *
 */
typedef struct
{
    char *hostname;     /**< XMPP server hostname */
    uint16_t   port;    /**< XMPP server serivce port */
    char *xmpp_domain;  /**< XMPP login domain */
    char *username;     /**< login username */
    char *password;     /**< login password */
    char *resource;     /**< specific resource for login */
    char *user_jid;     /**< specific JID for login */
    jid_bound_cb jidbound;  /**< callback when JID bound */
} OCRAInfo_t;
#endif  /* RA_ADAPTER */


/** Enum to describe the type of object held by the OCPayload object.*/
typedef enum
{
    /** Contents of the payload are invalid */
    PAYLOAD_TYPE_INVALID,
    /** The payload is an OCDiscoveryPayload */
    PAYLOAD_TYPE_DISCOVERY,
    /** The payload is an OCDevicePayload */
    PAYLOAD_TYPE_DEVICE,
    /** The payload is an OCPlatformPayload */
    PAYLOAD_TYPE_PLATFORM,
    /** The payload is an OCRepPayload */
    PAYLOAD_TYPE_REPRESENTATION,
    /** The payload is an OCSecurityPayload */
    PAYLOAD_TYPE_SECURITY,
    /** The payload is an OCPresencePayload */
    PAYLOAD_TYPE_PRESENCE,
    /** The payload is an OCRDPayload */
    PAYLOAD_TYPE_RD
} OCPayloadType;

/**
 * A generic struct representing a payload returned from a resource operation
 *
 * A pointer to OCPayLoad can be cast to a more specific struct to access members
 * for the its type.
 */
typedef struct
{
    /** The type of message that was received */
    OCPayloadType type;
} OCPayload;

typedef enum
{
    OCREP_PROP_NULL,
    OCREP_PROP_INT,
    OCREP_PROP_DOUBLE,
    OCREP_PROP_BOOL,
    OCREP_PROP_STRING,
    OCREP_PROP_BYTE_STRING,
    OCREP_PROP_OBJECT,
    OCREP_PROP_ARRAY
}OCRepPayloadPropType;

/** This structure will be used to represent a binary string for CBOR payloads.*/
typedef struct
{
    /** pointer to data bytes.*/
    uint8_t* bytes;

    /** number of data bytes.*/
    size_t   len;
} OCByteString;

#define MAX_REP_ARRAY_DEPTH 3
typedef struct
{
    OCRepPayloadPropType type;
    size_t dimensions[MAX_REP_ARRAY_DEPTH];

    union
    {
        int64_t* iArray;
        double* dArray;
        bool* bArray;
        char** strArray;

        /** pointer to ByteString array.*/
        OCByteString* ocByteStrArray;

        struct OCRepPayload** objArray;
    };
} OCRepPayloadValueArray;

typedef struct OCRepPayloadValue
{
    char* name;
    OCRepPayloadPropType type;
    union
    {
        int64_t i;
        double d;
        bool b;
        char* str;

        /** ByteString object.*/
        OCByteString ocByteStr;

        struct OCRepPayload* obj;
        OCRepPayloadValueArray arr;
    };
    struct OCRepPayloadValue* next;

} OCRepPayloadValue;

// used for get/set/put/observe/etc representations
typedef struct OCRepPayload
{
    OCPayload base;
    char* uri;
    OCStringLL* types;
    OCStringLL* interfaces;
    OCRepPayloadValue* values;
    struct OCRepPayload* next;
} OCRepPayload;

// used inside a discovery payload
typedef struct OCResourcePayload
{
    char* uri;
    OCStringLL* types;
    OCStringLL* interfaces;
    uint8_t bitmap;
    bool secure;
    uint16_t port;
#ifdef TCP_ADAPTER
    uint16_t tcpPort;
#endif
    struct OCResourcePayload* next;
} OCResourcePayload;

/**
 * Structure holding Links Payload. It is a sub-structure used in
 * OCResourceCollectionPayload.
 */
typedef struct OCLinksPayload
{
    /** This is the target relative URI. */
    char *href;
    /** Resource Type - A standard OIC specified or vendor defined resource
     * type of the resource referenced by the target URI. */
    OCStringLL *rt;
    /** Interface - The interfaces supported by the resource referenced by the target URI. */
    OCStringLL *itf;
    /** The relation of the target URI referenced by the link to the context URI;
     * The default value is null. */
    char *rel;
    /** Specifies if the resource referenced by the target URIis observable or not. */
    bool obs;
    /** A title for the link relation. Can be used by the UI to provide a context. */
    char *title;
    /** This is used to override the context URI e.g. override the URI of the containing collection. */
    char *uri;
    /** The instance identifier for this web link in an array of web links - used in links. */
    union
    {
        /** An ordinal number that is not repeated - must be unique in the collection context. */
        uint8_t ins;
        /** Any unique string including a URI. */
        char *uniqueStr;
        /** Use UUID for universal uniqueness - used in /oic/res to identify the device. */
        OCIdentity uniqueUUID;
    };
    /** A hint of the media type of the representation of the resource referenced by the target URI. */
    OCStringLL *mt;
    /** Holding address of the next resource. */
    struct OCLinksPayload *next;
} OCLinksPayload;

/** Structure holding tags value of the links payload. */
typedef struct
{
    /** Name of tags. */
    OCDeviceInfo n;
    /** Device identifier. */
    OCIdentity di;
    /** The base URI where the resources are hold. */
    char *baseURI;
    /** Bitmap holds observable, discoverable, secure option flag.*/
    uint8_t bitmap;
    /** Port set in case, the secure flag is set above. */
    uint16_t port;
    /** Id for each set of links i.e. tag. */
    union
    {
        /** An ordinal number that is not repeated - must be unique in the collection context. */
        uint8_t ins;
        /** Any unique string including a URI. */
        char *uniqueStr;
        /** Use UUID for universal uniqueness - used in /oic/res to identify the device. */
        OCIdentity uniqueUUID;
    };
    /** Defines the list of allowable resource types (for Target and anchors) in links included
     * in the collection; new links being created can only be from this list. */
    char *rts;
    /** When specified this is the default relationship to use when an OIC Link does not specify
     * an explicit relationship with *rel* parameter. */
    char *drel;
    /** Time to keep holding resource.*/
    uint32_t ttl;
} OCTagsPayload;

/** Resource collection payload. */
typedef struct OCResourceCollectionPayload
{
    /** Collection tags payload.*/
    OCTagsPayload *tags;
    /** Array of links payload. */
    OCLinksPayload *setLinks;
    /** Holding address of the next resource. */
    struct OCResourceCollectionPayload *next;
} OCResourceCollectionPayload;

typedef struct OCDiscoveryPayload
{
    OCPayload base;

    /** Device Id */
    char *sid;

    /** A special case for handling RD address. */
    char* baseURI;

    /** Name */
    char *name;

    /** HREF */
    char *uri;

    /** Resource Type */
    OCStringLL *type;

    /** Interface */
    OCStringLL *iface;

    /** This structure holds the old /oic/res response. */
    OCResourcePayload *resources;

    /** Holding address of the next DiscoveryPayload. */
    struct OCDiscoveryPayload *next;

} OCDiscoveryPayload;

/**
 * Structure holding discovery payload.
 */
typedef struct
{
    /** Device Name. */
    OCDeviceInfo n;
    /** Device Identity. */
    OCIdentity di;
    /** Value holding the bias factor of the RD. */
    uint8_t sel;
} OCRDDiscoveryPayload;

/**
 * RD Payload that will be transmitted over the wire.
 */
typedef struct
{
    OCPayload base;
    /** Pointer to the discovery response payload.*/
    OCRDDiscoveryPayload *rdDiscovery;
    /** Pointer to the publish payload.*/
    OCResourceCollectionPayload *rdPublish;
} OCRDPayload;

typedef struct
{
    OCPayload base;
    char *sid;
    char* deviceName;
    char* specVersion;
    OCStringLL *dataModelVersions;
    OCStringLL *interfaces;
    OCStringLL *types;
} OCDevicePayload;

typedef struct
{
    OCPayload base;
    char* uri;
    OCPlatformInfo info;
    OCStringLL* rt;
    OCStringLL* interfaces;
} OCPlatformPayload;

typedef struct
{
    OCPayload base;
    uint8_t* securityData;
    size_t payloadSize;
} OCSecurityPayload;

#ifdef WITH_PRESENCE
typedef struct
{
    OCPayload base;
    uint32_t sequenceNumber;
    uint32_t maxAge;
    OCPresenceTrigger trigger;
    char* resourceType;
} OCPresencePayload;
#endif

/**
 * Incoming requests handled by the server. Requests are passed in as a parameter to the
 * OCEntityHandler callback API.
 * The OCEntityHandler callback API must be implemented in the application in order
 * to receive these requests.
 */
typedef struct
{
    /** Associated resource.*/
    OCResourceHandle resource;

    /** Associated request handle.*/
    OCRequestHandle requestHandle;

    /** the REST method retrieved from received request PDU.*/
    OCMethod method;

    /** description of endpoint that sent the request.*/
    OCDevAddr devAddr;

    /** resource query send by client.*/
    char * query;

    /** Information associated with observation - valid only when OCEntityHandler flag includes
     * ::OC_OBSERVE_FLAG.*/
    OCObservationInfo obsInfo;

    /** Number of the received vendor specific header options.*/
    uint8_t numRcvdVendorSpecificHeaderOptions;

    /** Pointer to the array of the received vendor specific header options.*/
    OCHeaderOption * rcvdVendorSpecificHeaderOptions;

    /** Message id.*/
    uint16_t messageID;

    /** the payload from the request PDU.*/
    OCPayload *payload;

} OCEntityHandlerRequest;


/**
 * Response from queries to remote servers. Queries are made by calling the OCDoResource API.
 */
typedef struct
{
    /** Address of remote server.*/
    OCDevAddr devAddr;

    /** backward compatibility (points to devAddr).*/
    OCDevAddr *addr;

    /** backward compatibility.*/
    OCConnectivityType connType;

    /** the security identity of the remote server.*/
    OCIdentity identity;

    /** the is the result of our stack, OCStackResult should contain coap/other error codes.*/
    OCStackResult result;

    /** If associated with observe, this will represent the sequence of notifications from server.*/
    uint32_t sequenceNumber;

    /** resourceURI.*/
    const char * resourceUri;

    /** the payload for the response PDU.*/
    OCPayload *payload;

    /** Number of the received vendor specific header options.*/
    uint8_t numRcvdVendorSpecificHeaderOptions;

    /** An array of the received vendor specific header options.*/
    OCHeaderOption rcvdVendorSpecificHeaderOptions[MAX_HEADER_OPTIONS];
} OCClientResponse;

/**
 * Request handle is passed to server via the entity handler for each incoming request.
 * Stack assigns when request is received, server sets to indicate what request response is for.
 */
typedef struct
{
    /** Request handle.*/
    OCRequestHandle requestHandle;

    /** Resource handle.*/
    OCResourceHandle resourceHandle;

    /** Allow the entity handler to pass a result with the response.*/
    OCEntityHandlerResult  ehResult;

    /** This is the pointer to server payload data to be transferred.*/
    OCPayload* payload;

    /** number of the vendor specific header options .*/
    uint8_t numSendVendorSpecificHeaderOptions;

    /** An array of the vendor specific header options the entity handler wishes to use in response.*/
    OCHeaderOption sendVendorSpecificHeaderOptions[MAX_HEADER_OPTIONS];

    /** URI of new resource that entity handler might create.*/
    char resourceUri[MAX_URI_LENGTH];

    /** Server sets to true for persistent response buffer,false for non-persistent response buffer*/
    uint8_t persistentBufferFlag;
} OCEntityHandlerResponse;

/**
 * Entity's state
 */
typedef enum
{
    /** Request state.*/
    OC_REQUEST_FLAG = (1 << 1),
    /** Observe state.*/
    OC_OBSERVE_FLAG = (1 << 2)
} OCEntityHandlerFlag;

/**
 * Possible return values from client application callback
 *
 * A client application callback returns an OCStackApplicationResult to indicate whether
 * the stack should continue to keep the callback registered.
 */
typedef enum
{
    /** Make no more calls to the callback and call the OCClientContextDeleter for this callback */
    OC_STACK_DELETE_TRANSACTION = 0,
    /** Keep this callback registered and call it if an apropriate event occurs */
    OC_STACK_KEEP_TRANSACTION
} OCStackApplicationResult;


//#ifdef DIRECT_PAIRING
/**
 * @brief   direct pairing Method Type.
 *              0:  not allowed
 *              1:  pre-configured pin
 *              2:  random pin
 */
typedef enum OCPrm
{
    DP_NOT_ALLOWED             = 0x0,
    DP_PRE_CONFIGURED        = (0x1 << 0),
    DP_RANDOM_PIN               = (0x1 << 1),
} OCPrm_t;

/**
 * Device Information of discoverd direct pairing device(s).
 */
typedef struct OCDPDev
{
    OCDevAddr               endpoint;
    OCConnectivityType   connType;
    uint16_t                     securePort;
    bool                  edp;
    OCPrm_t           *prm;
    size_t                prmLen;
    OCUUIdentity     deviceID;
    OCUUIdentity     rowner;
    struct OCDPDev *next;
} OCDPDev_t;
//#endif // DIRECT_PAIRING

/*
 * -------------------------------------------------------------------------------------------
 * Callback function definitions
 * -------------------------------------------------------------------------------------------
 */

/**
 * Client applications implement this callback to consume responses received from Servers.
 */
typedef OCStackApplicationResult (* OCClientResponseHandler)(void *context, OCDoHandle handle,
    OCClientResponse * clientResponse);

/**
 * Client applications using a context pointer implement this callback to delete the
 * context upon removal of the callback/context pointer from the internal callback-list.
 */
typedef void (* OCClientContextDeleter)(void *context);

/**
 * This info is passed from application to OC Stack when initiating a request to Server.
 */
typedef struct OCCallbackData
{
    /** Pointer to the context.*/
    void *context;

    /** The pointer to a function the stack will call to handle the requests.*/
    OCClientResponseHandler cb;

    /** A pointer to a function to delete the context when this callback is removed.*/
    OCClientContextDeleter cd;

#ifdef SUPPORTS_DEFAULT_CTOR
    OCCallbackData() = default;
    OCCallbackData(void* ctx, OCClientResponseHandler callback, OCClientContextDeleter deleter)
        :context(ctx), cb(callback), cd(deleter){}
#endif
} OCCallbackData;

/**
 * Application server implementations must implement this callback to consume requests OTA.
 * Entity handler callback needs to fill the resPayload of the entityHandlerRequest.
 */
typedef OCEntityHandlerResult (*OCEntityHandler)
(OCEntityHandlerFlag flag, OCEntityHandlerRequest * entityHandlerRequest, void* callbackParam);

/**
 * Device Entity handler need to use this call back instead of OCEntityHandler.
 */
typedef OCEntityHandlerResult (*OCDeviceEntityHandler)
(OCEntityHandlerFlag flag, OCEntityHandlerRequest * entityHandlerRequest, char* uri, void* callbackParam);

//#ifdef DIRECT_PAIRING
/**
 * Callback function definition of direct-pairing
 *
 * @param[OUT] ctx - user context returned in the callback.
 * @param[OUT] peer - pairing device info.
 * @param[OUT} result - It's returned with 'OC_STACK_XXX'. It will return 'OC_STACK_OK'
 *                                   if D2D pairing is success without error
 */
typedef void (*OCDirectPairingCB)(void *ctx, OCDPDev_t *peer, OCStackResult result);
//#endif // DIRECT_PAIRING

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* OCTYPES_H_ */
