#ifndef PROTOCOL_COMMON_H
#define PROTOCOL_COMMON_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Common message structure (all protocols use the same layout)
typedef struct {
    int version;
    char device_id[64];
    int temperature;
    bool active;
} common_message;

// Common protocol functions (used internally by protocol-specific implementations)
bool protocol_common_parse(const char* buffer, size_t buffer_len, common_message* out);
int protocol_common_serialize(const common_message* msg, char* buffer, size_t buffer_size);
bool protocol_common_validate(const common_message* msg);
unsigned int protocol_common_checksum(const common_message* msg);

#ifdef __cplusplus
}
#endif

#endif

