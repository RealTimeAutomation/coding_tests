#ifndef LEGACY_PROTOCOL_CARROT_H
#define LEGACY_PROTOCOL_CARROT_H

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
} carrot_message;

// Parse carrot protocol message from buffer
// Returns true on success, false on parse error
bool carrot_parse(const char* buffer, size_t buffer_len, carrot_message* out);

// Serialize carrot message to buffer
// Returns number of bytes written, or -1 on error
int carrot_serialize(const carrot_message* msg, char* buffer, size_t buffer_size);

// Validate carrot message
bool carrot_validate(const carrot_message* msg);

// Get carrot message checksum
unsigned int carrot_checksum(const carrot_message* msg);

#ifdef __cplusplus
}
#endif

#endif

