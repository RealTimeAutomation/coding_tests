#include "cunit.h"
#include "protocol_carrot.h"
#include <string.h>

CUNIT_TEST(test_carrot_parse_basic) {
    // Format: 4-char version hex, 64-char device_id, 8-char temp hex, 1-char active
    char buffer[80] = "0001";
    memset(buffer + 4, 0, 64);
    strcpy(buffer + 4, "device123");
    strcpy(buffer + 68, "00000014"); // temp = 20
    buffer[76] = '1';
    buffer[77] = '\0';
    
    carrot_message msg;
    bool ok = carrot_parse(buffer, 77, &msg);
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(msg.version, 1);
    CUNIT_ASSERT_STR_EQ(msg.device_id, "device123");
    CUNIT_ASSERT_EQ(msg.temperature, 20);
    CUNIT_ASSERT(msg.active == true);
}

CUNIT_TEST(test_carrot_serialize_basic) {
    carrot_message msg;
    msg.version = 2;
    strcpy(msg.device_id, "test_device");
    msg.temperature = 25;
    msg.active = false;
    
    char buffer[128];
    int written = carrot_serialize(&msg, buffer, sizeof(buffer));
    CUNIT_ASSERT(written > 0);
}

CUNIT_TEST(test_carrot_serialize_roundtrip) {
    carrot_message original;
    original.version = 0x00BB;
    strcpy(original.device_id, "carrot_test");
    original.temperature = 300;
    original.active = true;
    
    char buffer[128];
    int written = carrot_serialize(&original, buffer, sizeof(buffer));
    CUNIT_ASSERT(written > 0);
    
    carrot_message parsed;
    bool ok = carrot_parse(buffer, written, &parsed);
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(parsed.version, original.version);
    CUNIT_ASSERT_STR_EQ(parsed.device_id, original.device_id);
    CUNIT_ASSERT_EQ(parsed.temperature, original.temperature);
}

CUNIT_TEST(test_carrot_validate_valid) {
    carrot_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "valid_carrot");
    msg.temperature = 150;
    msg.active = false;
    
    bool valid = carrot_validate(&msg);
    CUNIT_ASSERT(valid);
}

// Intentionally skipping tests for: NULL pointers, invalid buffer sizes, malformed input, edge cases, validation failures

