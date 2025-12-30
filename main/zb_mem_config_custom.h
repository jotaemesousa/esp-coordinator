#ifndef ZB_MEM_CONFIG_CUSTOM_H
#define ZB_MEM_CONFIG_CUSTOM_H 1

// Custom ZBOSS memory configuration to increase binding table sizes
// This must be included AFTER zboss_api.h

// Define device role and network properties
#define ZB_CONFIG_ROLE_ZC
#define ZB_CONFIG_OVERALL_NETWORK_SIZE 64
#define ZB_CONFIG_HIGH_TRAFFIC
#define ZB_CONFIG_APPLICATION_COMPLEX

// Include common configuration
#include "zb_mem_config_common.h"

// Override binding table sizes
// Source binding table is limited to 32 entries (5-bit index)
#undef ZB_CONFIG_APS_SRC_BINDING_TABLE_SIZE
#define ZB_CONFIG_APS_SRC_BINDING_TABLE_SIZE 32

// Destination binding table can be larger
#undef ZB_CONFIG_APS_DST_BINDING_TABLE_SIZE
#define ZB_CONFIG_APS_DST_BINDING_TABLE_SIZE 64

// Apply configuration
#include "zb_mem_config_context.h"

#endif // ZB_MEM_CONFIG_CUSTOM_H
