#include "cunit.h"
#include "protocol_carrot.h"
#include <string.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_carrot_parse_null_buffer) {
    carrot_message msg;
    bool result = carrot_parse(NULL, 77, &msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_carrot_parse_null_out) {
    char buffer[80] = "0001";
    bool result = carrot_parse(buffer, 77, NULL);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_carrot_parse_small_buffer) {
    char buffer[20] = "0001";
    carrot_message msg;
    bool result = carrot_parse(buffer, 20, &msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_carrot_serialize_null_msg) {
    char buffer[128];
    int result = carrot_serialize(NULL, buffer, sizeof(buffer));
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_carrot_serialize_null_buffer) {
    carrot_message msg;
    msg.version = 1;
    strcpy(msg.device_id, "test");
    msg.temperature = 10;
    msg.active = true;
    
    int result = carrot_serialize(&msg, NULL, 128);
    CUNIT_ASSERT_EQ(result, -1);
}

CUNIT_TEST(test_carrot_validate_null) {
    bool result = carrot_validate(NULL);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_carrot_validate_empty_device_id) {
    carrot_message msg;
    msg.version = 1;
    msg.device_id[0] = '\0';
    msg.temperature = 10;
    msg.active = true;
    
    bool result = carrot_validate(&msg);
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_carrot_checksum_null) {
    unsigned int result = carrot_checksum(NULL);
    CUNIT_ASSERT(result == 0 || result != 0);
}

