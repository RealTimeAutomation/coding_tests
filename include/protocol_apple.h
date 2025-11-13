#ifndef LEGACY_PROTOCOL_APPLE_H
#define LEGACY_PROTOCOL_APPLE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int version;
    char device_id[64];
    int temperature;
    bool active;
} apple_message;

// Parse apple protocol message from buffer
// Returns true on success, false on parse error
bool apple_parse(const char* buffer, size_t buffer_len, apple_message* out);

// Serialize apple message to buffer
// Returns number of bytes written, or -1 on error
int apple_serialize(const apple_message* msg, char* buffer, size_t buffer_size);

// Validate apple message
bool apple_validate(const apple_message* msg);

// Get apple message checksum
unsigned int apple_checksum(const apple_message* msg);

#ifdef __cplusplus
}
#endif

#endif

