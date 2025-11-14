/**
 * @file protocol_banana.h
 * @brief Banana protocol message serialization and parsing
 * 
 * This module provides functions to parse, serialize, validate, and compute
 * checksums for Banana protocol messages. The protocol uses a binary format
 * with fixed-size fields.
 * 
 * Protocol Format:
 * - Version: 4 hex digits (0-65535)
 * - Device ID: Up to 63 characters, padded to 64 bytes with nulls
 * - Temperature: 8 hex digits (signed integer, -1000 to 1000)
 * - Active: 1 character ('0' or '1')
 * - Minimum buffer size: 77 bytes
 */

#ifndef LEGACY_PROTOCOL_BANANA_H
#define LEGACY_PROTOCOL_BANANA_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Banana protocol message structure
 */
typedef struct {
    int version;           /**< Protocol version (0-65535) */
    char device_id[64];     /**< Device identifier (null-terminated, max 63 chars) */
    int temperature;        /**< Temperature value (-1000 to 1000) */
    bool active;           /**< Active status flag */
} banana_message;

/**
 * @brief Parses a Banana protocol message from a buffer
 * 
 * @param buffer Buffer containing the message (can be NULL)
 * @param buffer_len Length of the buffer in bytes
 * @param out Pointer to message structure to populate (can be NULL)
 * @return true if parsing succeeded, false on error
 * 
 * @note Returns false if buffer is NULL, out is NULL, or buffer_len < 77
 * @note Returns false if version is out of range (0-65535)
 * @note Returns false if temperature parsing fails
 * @note Returns false if active flag is not '0' or '1'
 * @note Device ID is copied up to 63 characters or until null/pipe character
 * 
 * @example
 *   banana_message msg;
 *   if (banana_parse(buffer, buffer_len, &msg)) {
 *       // Use msg.version, msg.device_id, msg.temperature, msg.active
 *   }
 */
bool banana_parse(const char* buffer, size_t buffer_len, banana_message* out);

/**
 * @brief Serializes a Banana protocol message to a buffer
 * 
 * @param msg Message to serialize (can be NULL)
 * @param buffer Buffer to write to (can be NULL)
 * @param buffer_size Size of the buffer in bytes
 * @return Number of bytes written, or -1 on error
 * 
 * @note Returns -1 if msg is NULL, buffer is NULL, or buffer_size < 77
 * @note Version is formatted as 4 uppercase hex digits
 * @note Device ID is padded to 64 bytes with nulls
 * @note Temperature is formatted as 8 uppercase hex digits
 * @note Active is written as '1' or '0'
 * 
 * @example
 *   char buffer[128];
 *   int written = banana_serialize(&msg, buffer, sizeof(buffer));
 *   if (written > 0) {
 *       // buffer contains serialized message
 *   }
 */
int banana_serialize(const banana_message* msg, char* buffer, size_t buffer_size);

/**
 * @brief Validates a Banana protocol message
 * 
 * @param msg Message to validate (can be NULL)
 * @return true if message is valid, false otherwise
 * 
 * @note Returns false if msg is NULL
 * @note Validates version is in range 0-65535
 * @note Validates device_id is non-empty
 * @note Validates device_id contains only printable ASCII (32-126)
 * @note Validates temperature is in range -1000 to 1000
 * 
 * @example
 *   if (banana_validate(&msg)) {
 *       // Message is valid
 *   }
 */
bool banana_validate(const banana_message* msg);

/**
 * @brief Computes a checksum for a Banana protocol message
 * 
 * @param msg Message to checksum (can be NULL)
 * @return Checksum value, or 0 if msg is NULL
 * 
 * @note Checksum is sum of: version + temperature + active (0 or 1) + sum of device_id bytes
 * @note Returns 0 for NULL message
 * 
 * @example
 *   unsigned int sum = banana_checksum(&msg);
 */
unsigned int banana_checksum(const banana_message* msg);

#ifdef __cplusplus
}
#endif

#endif

