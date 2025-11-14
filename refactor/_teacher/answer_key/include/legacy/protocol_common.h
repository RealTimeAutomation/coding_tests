/**
 * @file protocol_common.h
 * @brief Shared protocol implementation for Apple, Banana, and Carrot protocols
 * 
 * This is an internal header used by the protocol-specific implementations.
 * All three protocols (apple, banana, carrot) share the same message format
 * and use these common functions for parsing, serialization, validation, and
 * checksum computation.
 * 
 * @note This header is for internal use only. Use protocol_apple.h,
 *       protocol_banana.h, or protocol_carrot.h for the public API.
 */

#ifndef PROTOCOL_COMMON_H
#define PROTOCOL_COMMON_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Common message structure (all protocols use the same layout)
 * 
 * This structure is used internally by all three protocol implementations.
 * The protocol-specific message types (apple_message, banana_message, carrot_message)
 * have identical layouts and can be safely cast to/from this type.
 */
typedef struct {
    int version;           /**< Protocol version (0-65535) */
    char device_id[64];     /**< Device identifier (null-terminated, max 63 chars) */
    int temperature;        /**< Temperature value (-1000 to 1000) */
    bool active;           /**< Active status flag */
} common_message;

/**
 * @brief Common parse function (internal use only)
 * 
 * @param buffer Buffer containing the message
 * @param buffer_len Length of the buffer in bytes
 * @param out Pointer to common_message structure to populate
 * @return true if parsing succeeded, false on error
 * 
 * @internal
 */
bool protocol_common_parse(const char* buffer, size_t buffer_len, common_message* out);

/**
 * @brief Common serialize function (internal use only)
 * 
 * @param msg Message to serialize
 * @param buffer Buffer to write to
 * @param buffer_size Size of the buffer in bytes
 * @return Number of bytes written, or -1 on error
 * 
 * @internal
 */
int protocol_common_serialize(const common_message* msg, char* buffer, size_t buffer_size);

/**
 * @brief Common validate function (internal use only)
 * 
 * @param msg Message to validate
 * @return true if message is valid, false otherwise
 * 
 * @internal
 */
bool protocol_common_validate(const common_message* msg);

/**
 * @brief Common checksum function (internal use only)
 * 
 * @param msg Message to checksum
 * @return Checksum value, or 0 if msg is NULL
 * 
 * @internal
 */
unsigned int protocol_common_checksum(const common_message* msg);

#ifdef __cplusplus
}
#endif

#endif

