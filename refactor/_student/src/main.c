#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"
#include "protocol_apple.h"
#include "protocol_banana.h"
#include "protocol_carrot.h"
#include "logger.h"

static void test_generic_protocol(void) {
    log_info("Testing Generic Protocol");

    // Create a test message
    gen_message msg = {
        .version = 0x0001,
        .device_id = "APPLE_DEVICE_001",
        .temperature = 250,
        .active = true
    };

    log_debug("Created message: version=0x%04X, device_id=%s, temp=%d, active=%d",
              msg.version, msg.device_id, msg.temperature, msg.active);

    // Serialize
    char buffer[256];
    int written = gen_serialize(&msg, buffer, sizeof(buffer));

    if (written < 0) {
        log_error("Failed to serialize message");
        return;
    }
    buffer[written] = '\0';
    
    log_info("Serialized message (%d bytes): %s", written, buffer);
    printf("Serialized message (%d bytes): %s\n", written, buffer);
    
    // Parse back
    gen_message parsed;
    if (gen_parse(buffer, written, &parsed)) {
        log_info("Parsed message successfully");
        log_debug("Parsed: version=0x%04X, device_id=%s, temp=%d, active=%d",
                  parsed.version, parsed.device_id, parsed.temperature, parsed.active);
        
        // Validate
        if (gen_validate(&parsed)) {
            log_info("Message validation: PASSED");
        } else {
            log_warn("Message validation: FAILED");
        }
        
        // Checksum
        unsigned int checksum = gen_checksum(&parsed);
        log_debug("Message checksum: 0x%08X", checksum);
    } else {
        log_error("Failed to parse message");
    }
    
};

static void test_apple_protocol(void) {
    log_info("Testing Apple Protocol");
    
    // Create a test message
    apple_message msg = {
        .version = 0x0001,
        .device_id = "APPLE_DEVICE_001",
        .temperature = 250,
        .active = true
    };
    
    log_debug("Created apple message: version=0x%04X, device_id=%s, temp=%d, active=%d",
              msg.version, msg.device_id, msg.temperature, msg.active);
    
    // Serialize
    char buffer[256];
    int written = apple_serialize(&msg, buffer, sizeof(buffer));

    if (written < 0) {
        log_error("Failed to serialize apple message");
        return;
    }
    buffer[written] = '\0';
    
    log_info("Serialized apple message (%d bytes): %s", written, buffer);
    
    // Parse back
    apple_message parsed;
    if (apple_parse(buffer, written, &parsed)) {
        log_info("Parsed apple message successfully");
        log_debug("Parsed: version=0x%04X, device_id=%s, temp=%d, active=%d",
                  parsed.version, parsed.device_id, parsed.temperature, parsed.active);
        
        // Validate
        if (apple_validate(&parsed)) {
            log_info("Apple message validation: PASSED");
        } else {
            log_warn("Apple message validation: FAILED");
        }
        
        // Checksum
        unsigned int checksum = apple_checksum(&parsed);
        log_debug("Apple message checksum: 0x%08X", checksum);
    } else {
        log_error("Failed to parse apple message");
    }
}

static void test_banana_protocol(void) {
    log_info("Testing Banana Protocol");
    
    // Create a test message
    banana_message msg = {
        .version = 0x0002,
        .device_id = "BANANA_DEVICE_002",
        .temperature = -100,
        .active = false
    };
    
    log_debug("Created banana message: version=0x%04X, device_id=%s, temp=%d, active=%d",
              msg.version, msg.device_id, msg.temperature, msg.active);
    
    // Serialize
    char buffer[256];
    int written = banana_serialize(&msg, buffer, sizeof(buffer));
    if (written < 0) {
        log_error("Failed to serialize banana message");
        return;
    }
    buffer[written] = '\0';
    
    log_info("Serialized banana message (%d bytes): %s", written, buffer);
    
    // Parse back
    banana_message parsed;
    if (banana_parse(buffer, written, &parsed)) {
        log_info("Parsed banana message successfully");
        log_debug("Parsed: version=0x%04X, device_id=%s, temp=%d, active=%d",
                  parsed.version, parsed.device_id, parsed.temperature, parsed.active);
        
        // Validate
        if (banana_validate(&parsed)) {
            log_info("Banana message validation: PASSED");
        } else {
            log_warn("Banana message validation: FAILED");
        }
        
        // Checksum
        unsigned int checksum = banana_checksum(&parsed);
        log_debug("Banana message checksum: 0x%08X", checksum);
    } else {
        log_error("Failed to parse banana message");
    }
}

static void test_carrot_protocol(void) {
    log_info("Testing Carrot Protocol");
    
    // Create a test message
    carrot_message msg = {
        .version = 0x0003,
        .device_id = "CARROT_DEVICE_003",
        .temperature = 500,
        .active = true
    };
    
    log_debug("Created carrot message: version=0x%04X, device_id=%s, temp=%d, active=%d",
              msg.version, msg.device_id, msg.temperature, msg.active);
    
    // Serialize
    char buffer[256];
    int written = carrot_serialize(&msg, buffer, sizeof(buffer));
    if (written < 0) {
        log_error("Failed to serialize carrot message");
        return;
    }
    buffer[written] = '\0';
    
    log_info("Serialized carrot message (%d bytes): %s", written, buffer);
    
    // Parse back
    carrot_message parsed;
    if (carrot_parse(buffer, written, &parsed)) {
        log_info("Parsed carrot message successfully");
        log_debug("Parsed: version=0x%04X, device_id=%s, temp=%d, active=%d",
                  parsed.version, parsed.device_id, parsed.temperature, parsed.active);
        
        // Validate
        if (carrot_validate(&parsed)) {
            log_info("Carrot message validation: PASSED");
        } else {
            log_warn("Carrot message validation: FAILED");
        }
        
        // Checksum
        unsigned int checksum = carrot_checksum(&parsed);
        log_debug("Carrot message checksum: 0x%08X", checksum);
    } else {
        log_error("Failed to parse carrot message");
    }
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
    
    // test_generic_protocol();
    // test_apple_protocol();
    
    test_all_protocols_interaction();
    
    log_info("Program completed");
    return 0;
}

