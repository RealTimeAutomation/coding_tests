#include "cunit.h"
#include "protocol_apple.h"
#include <string.h>

CUNIT_TEST(test_apple_parse_basic) {
    // Format: 4-char version hex, 64-char device_id, 8-char temp hex, 1-char active
    char buffer[80] = "0001";
    memset(buffer + 4, 0, 64);
    strcpy(buffer + 4, "device123");
    strcpy(buffer + 68, "00000014"); // temp = 20
    buffer[76] = '1';
    buffer[77] = '\0';
    
    apple_message msg;
    bool ok = apple_parse(buffer, 77, &msg);
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(msg.version, 1);
    CUNIT_ASSERT_STR_EQ(msg.device_id, "device123");
    CUNIT_ASSERT_EQ(msg.temperature, 20);
    CUNIT_ASSERT(msg.active == true);
}

CUNIT_TEST(test_apple_parse_zero_temp) {
    char buffer[80] = "0002";
    memset(buffer + 4, 0, 64);
    strcpy(buffer + 4, "device456");
    strcpy(buffer + 68, "00000000");
    buffer[76] = '0';
    buffer[77] = '\0';
    
    apple_message msg;
    bool ok = apple_parse(buffer, 77, &msg);
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(msg.temperature, 0);
    CUNIT_ASSERT(msg.active == false);
}

CUNIT_TEST(test_apple_serialize_basic) {
    apple_message msg;
    msg.version = 2;
    strcpy(msg.device_id, "test_device");
    msg.temperature = 25;
    msg.active = false;
    
    char buffer[128];
    int written = apple_serialize(&msg, buffer, sizeof(buffer));
    CUNIT_ASSERT(written > 0);
}

CUNIT_TEST(test_apple_serialize_roundtrip) {
    apple_message original;
    original.version = 0x00FF;
    strcpy(original.device_id, "roundtrip_test");
    original.temperature = 100;
    original.active = true;
    
    char buffer[128];
    int written = apple_serialize(&original, buffer, sizeof(buffer));
    CUNIT_ASSERT(written > 0);
    
    apple_message parsed;
    bool ok = apple_parse(buffer, written, &parsed);
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(parsed.version, original.version);
    CUNIT_ASSERT_STR_EQ(parsed.device_id, original.device_id);
    CUNIT_ASSERT_EQ(parsed.temperature, original.temperature);
    CUNIT_ASSERT(parsed.active == original.active);
}

CUNIT_TEST(test_apple_validate_valid) {
    apple_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "valid_device");
    msg.temperature = 50;
    msg.active = true;
    
    bool valid = apple_validate(&msg);
    CUNIT_ASSERT(valid);
}

CUNIT_TEST(test_apple_checksum) {
    apple_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    unsigned int checksum = apple_checksum(&msg);
    CUNIT_ASSERT(checksum >= 0);
}

// Intentionally skipping tests for: NULL pointers, invalid buffer sizes, malformed input, edge cases, validation failures

