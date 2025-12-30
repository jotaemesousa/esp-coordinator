# Zigbee Binding Table "Table Full" Fix

## Problem
When binding Zigbee sensors to the coordinator, users encountered "Table Full" errors preventing new devices from being bound.

## Root Cause
The ZBOSS stack uses default binding table sizes of 16 entries for both source and destination binding tables. This is insufficient for larger Zigbee networks with many sensors.

## Solution
Configure larger binding table sizes using ZBOSS compile-time memory configuration.

Created `main/zb_mem_config_custom.h` with custom memory settings:

```c
#define ZB_CONFIG_APS_SRC_BINDING_TABLE_SIZE 32  // Max 32 (5-bit index limit)
#define ZB_CONFIG_APS_DST_BINDING_TABLE_SIZE 64  // Can be larger
```

This header is included in `zb_ncp.cpp` after the ZBOSS API headers to override default table sizes.

### Key Points

1. **Compile-Time Configuration**: Uses ZBOSS memory configuration macros instead of runtime API calls.

2. **Source Table Limit**: The source binding table is limited to 32 entries due to ZBOSS using a 5-bit index for linking source and destination entries.

3. **Destination Table**: The destination binding table can be configured larger (64 entries in this fix).

4. **Memory Impact**: Larger tables consume more RAM. The current configuration balances capacity with memory usage.

5. **Include Order**: The custom config must be included AFTER `zboss_api.h` to properly override defaults.

## Binding Table Structure

ZBOSS splits binding information into two tables:

- **Source Binding Table**: Contains `src_addr`, `src_endpoint`, `cluster_id`
- **Destination Binding Table**: Contains `dst_address`, `dst_endpoint`

Each destination entry links to a source entry via a 5-bit index, which is why the source table is limited to 32 entries (2^5 = 32).

## Testing

After applying this fix:

1. Flash the updated firmware to your ESP32-C6
2. Pair Zigbee sensors with the coordinator
3. Create bindings between devices
4. Verify no "Table Full" errors occur
5. Monitor memory usage to ensure sufficient RAM remains

## Configuration Values

Current configuration:
- Source binding table: 32 entries (maximum possible)
- Destination binding table: 64 entries
- Max children: 64 devices

These values support networks with up to 32 unique binding sources and 64 binding destinations, which should be sufficient for most home automation setups.

## Future Enhancements

If you need more binding capacity:
- The destination table can be increased beyond 64 (memory permitting)
- The source table cannot exceed 32 due to ZBOSS architecture
- Consider using group addressing for devices that need the same commands

## References

- ESP Zigbee SDK Core API Documentation
- ZBOSS Memory Configuration Guide
- ESP-IDF Zigbee Library v1.6.6
- GitHub Issue espressif/esp-zigbee-sdk#694
