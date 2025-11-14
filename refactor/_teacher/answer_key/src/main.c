#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol_apple.h"
#include "protocol_banana.h"
#include "protocol_carrot.h"
#include "logger.h"

// Generic protocol test function using function pointers
// Since all protocol structs have identical layouts, we can use a union
typedef union {
    apple_message apple;
    banana_message banana;
    carrot_message carrot;
} protocol_message;

typedef struct {
    const char* name;
    int version;
    const char* device_id;
    int temperature;
    bool active;
    bool (*parse)(const char*, size_t, void*);
    int (*serialize)(const void*, char*, size_t);
    bool (*validate)(const void*);
    unsigned int (*checksum)(const void*);
} protocol_test_config;

static void test_protocol_generic(const protocol_test_config* config) {
    log_info("Testing %s Protocol", config->name);
    
    // Create a test message (all protocols have identical struct layout)
    protocol_message msg;
    msg.apple.version = config->version;
    strncpy(msg.apple.device_id, config->device_id, sizeof(msg.apple.device_id) - 1);
    msg.apple.device_id[sizeof(msg.apple.device_id) - 1] = '\0';
    msg.apple.temperature = config->temperature;
    msg.apple.active = config->active;
    
    log_debug("Created %s message: version=0x%04X, device_id=%s, temp=%d, active=%d",
              config->name, msg.apple.version, msg.apple.device_id, 
              msg.apple.temperature, msg.apple.active);
    
    // Serialize
    char buffer[256];
    int written = config->serialize(&msg, buffer, sizeof(buffer));
    if (written < 0) {
        log_error("Failed to serialize %s message", config->name);
        return;
    }
    buffer[written] = '\0';
    
    log_info("Serialized %s message (%d bytes): %s", config->name, written, buffer);
    
    // Parse back
    protocol_message parsed;
    if (config->parse(buffer, written, &parsed)) {
        log_info("Parsed %s message successfully", config->name);
        log_debug("Parsed: version=0x%04X, device_id=%s, temp=%d, active=%d",
                  parsed.apple.version, parsed.apple.device_id, 
                  parsed.apple.temperature, parsed.apple.active);
        
        // Validate
        if (config->validate(&parsed)) {
            log_info("%s message validation: PASSED", config->name);
        } else {
            log_warn("%s message validation: FAILED", config->name);
        }
        
        // Checksum
        unsigned int checksum = config->checksum(&parsed);
        log_debug("%s message checksum: 0x%08X", config->name, checksum);
    } else {
        log_error("Failed to parse %s message", config->name);
    }
}

static void test_apple_protocol(void) {
    protocol_test_config config = {
        .name = "Apple",
        .version = 0x0001,
        .device_id = "APPLE_DEVICE_001",
        .temperature = 250,
        .active = true,
        .parse = (bool(*)(const char*, size_t, void*))apple_parse,
        .serialize = (int(*)(const void*, char*, size_t))apple_serialize,
        .validate = (bool(*)(const void*))apple_validate,
        .checksum = (unsigned int(*)(const void*))apple_checksum
    };
    test_protocol_generic(&config);
}

static void test_banana_protocol(void) {
    protocol_test_config config = {
        .name = "Banana",
        .version = 0x0002,
        .device_id = "BANANA_DEVICE_002",
        .temperature = -100,
        .active = false,
        .parse = (bool(*)(const char*, size_t, void*))banana_parse,
        .serialize = (int(*)(const void*, char*, size_t))banana_serialize,
        .validate = (bool(*)(const void*))banana_validate,
        .checksum = (unsigned int(*)(const void*))banana_checksum
    };
    test_protocol_generic(&config);
}

static void test_carrot_protocol(void) {
    protocol_test_config config = {
        .name = "Carrot",
        .version = 0x0003,
        .device_id = "CARROT_DEVICE_003",
        .temperature = 500,
        .active = true,
        .parse = (bool(*)(const char*, size_t, void*))carrot_parse,
        .serialize = (int(*)(const void*, char*, size_t))carrot_serialize,
        .validate = (bool(*)(const void*))carrot_validate,
        .checksum = (unsigned int(*)(const void*))carrot_checksum
    };
    test_protocol_generic(&config);
}

static void test_all_protocols_interaction(void) {
    log_info("=== Testing All Protocols Interaction ===");
    
    // Test round-trip for all three protocols
    test_apple_protocol();
    printf("\n");
    
    test_banana_protocol();
    printf("\n");
    
    test_carrot_protocol();
    printf("\n");
    
    log_info("=== All Protocol Tests Complete ===");
}

int main(int argc, char* argv[]) {
    // Initialize logger (reads LOG_LEVEL from environment)
    logger_init();
    
    log_info("Starting protocol demonstration program");
    log_debug("Log level: %s", 
              logger_get_level() == LOG_NONE ? "NONE" :
              logger_get_level() == LOG_ERROR ? "ERROR" :
              logger_get_level() == LOG_WARN ? "WARN" :
              logger_get_level() == LOG_INFO ? "INFO" : "DEBUG");
    
    // If LOG_LEVEL is NONE, still show basic output
    if (logger_get_level() == LOG_NONE) {
        printf("Protocol Demonstration\n");
        printf("=====================\n\n");
    }
    
    test_all_protocols_interaction();
    
    log_info("Program completed");
    return 0;
}

