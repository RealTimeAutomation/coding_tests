#include "cunit.h"
#include "protocol_banana.h"
#include <string.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_banana_parse_null_buffer) {
    banana_message msg;
    bool result = banana_parse(NULL, 77, &msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_banana_parse_null_out) {
    char buffer[80] = "0001";
    bool result = banana_parse(buffer, 77, NULL);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_banana_parse_small_buffer) {
    char buffer[20] = "0001";
    banana_message msg;
    bool result = banana_parse(buffer, 20, &msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_banana_serialize_null_msg) {
    char buffer[128];
    int result = banana_serialize(NULL, buffer, sizeof(buffer));
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_banana_serialize_null_buffer) {
    banana_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    int result = banana_serialize(&msg, NULL, 128);
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_banana_validate_null) {
    bool result = banana_validate(NULL);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_banana_validate_empty_device_id) {
    banana_message msg;
    msg.version = 1;
    msg.device_id[0] = '\0';
    msg.temperature = 10;
    msg.active = true;
    
    bool result = banana_validate(&msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_banana_checksum_null) {
    unsigned int result = banana_checksum(NULL);
    CUNIT_ASSERT(result == 0 || result != 0);
}

