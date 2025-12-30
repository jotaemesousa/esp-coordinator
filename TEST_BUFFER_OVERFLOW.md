# RX Buffer Overflow Fix - Test Cases

## Bug Description
The `protocol::on_rx_int()` function had incorrect buffer overflow handling logic that could cause:
- Data corruption when buffer fills up
- Incorrect memory operations
- Potential crashes

## Fix Applied
- Added check to reject incoming data larger than buffer size
- Fixed overflow calculation and memmove logic to properly discard oldest data
- Improved logging to track buffer overflow events

## Test Cases

### Test Case 1: Normal Operation
**Input:** Small data packets that fit in buffer
**Expected:** Data is appended correctly, no overflow handling triggered
**Verification:** Check that `m_rx_buffer_pos` increases correctly

### Test Case 2: Buffer Near Full
**Input:** Data that would exceed RX_BUFFER_SIZE (1024 bytes)
**Expected:** 
- Oldest data is discarded to make room
- Warning log: "Buffer overflow, discarding X oldest bytes"
- New data is appended successfully
**Verification:** 
- `m_rx_buffer_pos` should be less than RX_BUFFER_SIZE after operation
- Buffer should contain newest data

### Test Case 3: Incoming Data Larger Than Buffer
**Input:** Single data packet > 1024 bytes
**Expected:**
- Function returns ESP_ERR_NO_MEM
- Error log: "Incoming data size X exceeds buffer size 1024"
- Buffer state unchanged
**Verification:** Return value is ESP_ERR_NO_MEM

### Test Case 4: Multiple Small Packets Causing Overflow
**Input:** Series of small packets that cumulatively exceed buffer size
**Expected:**
- Each packet triggers overflow handling as needed
- Oldest data is progressively discarded
- System continues to operate without crashes
**Verification:** No crashes, newest data is preserved

## Manual Testing Procedure

1. Flash the firmware to ESP32-C6
2. Connect to zigbee2mqtt
3. Monitor logs for buffer overflow warnings
4. Generate high traffic to trigger buffer overflow conditions
5. Verify system stability and correct packet processing

## Automated Testing (Future)

To implement automated tests:
1. Set up ESP-IDF component test framework
2. Create mock data generator
3. Implement test cases above with assertions
4. Add to CI/CD pipeline
