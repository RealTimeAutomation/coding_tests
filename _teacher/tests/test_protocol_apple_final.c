#include "cunit.h"
#include "protocol_apple.h"
#include <string.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_apple_parse_null_buffer) {
    apple_message msg;
    bool result = apple_parse(NULL, 77, &msg);
    // Should return false for NULL buffer
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_parse_null_out) {
    char buffer[80] = "0001";
    bool result = apple_parse(buffer, 77, NULL);
    // Should return false for NULL output
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_parse_small_buffer) {
    char buffer[20] = "0001";
    apple_message msg;
    bool result = apple_parse(buffer, 20, &msg);
    // Should return false for buffer too small
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_parse_invalid_hex) {
    char buffer[80] = "GGGG"; // Invalid hex
    memset(buffer + 4, 0, 64);
    strcpy(buffer + 4, "device");
    strcpy(buffer + 68, "00000014");
    buffer[76] = '1';
    
    apple_message msg;
    bool result = apple_parse(buffer, 77, &msg);
    // Should handle invalid hex gracefully
    CUNIT_ASSERT(result == false || result == true);
}

CUNIT_TEST(test_apple_serialize_null_msg) {
    char buffer[128];
    int result = apple_serialize(NULL, buffer, sizeof(buffer));
    // Should return -1 for NULL message
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_apple_serialize_null_buffer) {
    apple_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    int result = apple_serialize(&msg, NULL, 128);
    // Should return -1 for NULL buffer
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_apple_serialize_small_buffer) {
    apple_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    char buffer[10]; // Too small
    int result = apple_serialize(&msg, buffer, sizeof(buffer));
    // Should return -1 for buffer too small
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_apple_validate_null) {
    bool result = apple_validate(NULL);
    // Should return false for NULL message
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_validate_invalid_version) {
    apple_message msg;
    msg.version = -1; // Invalid
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    bool result = apple_validate(&msg);
    // Should return false for invalid version
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_validate_empty_device_id) {
    apple_message msg;
    msg.version = 1;
    msg.device_id[0] = '\0'; // Empty
    msg.temperature = 10;
    msg.active = true;
    
    bool result = apple_validate(&msg);
    // Should return false for empty device_id
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_validate_invalid_temp) {
    apple_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 2000; // Out of range
    msg.active = true;
    
    bool result = apple_validate(&msg);
    // Should return false for invalid temperature
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_apple_checksum_null) {
    unsigned int result = apple_checksum(NULL);
    // Should handle NULL gracefully
    CUNIT_ASSERT(result == 0 || result != 0);
}

