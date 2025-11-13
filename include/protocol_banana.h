#ifndef LEGACY_PROTOCOL_BANANA_H
#define LEGACY_PROTOCOL_BANANA_H

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
} banana_message;

// Parse banana protocol message from buffer
// Returns true on success, false on parse error
bool banana_parse(const char* buffer, size_t buffer_len, banana_message* out);

// Serialize banana message to buffer
// Returns number of bytes written, or -1 on error
int banana_serialize(const banana_message* msg, char* buffer, size_t buffer_size);

// Validate banana message
bool banana_validate(const banana_message* msg);

// Get banana message checksum
unsigned int banana_checksum(const banana_message* msg);

#ifdef __cplusplus
}
#endif

#endif

