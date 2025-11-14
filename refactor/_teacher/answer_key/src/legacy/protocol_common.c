#include "legacy/protocol_common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Protocol field sizes
#define VERSION_HEX_DIGITS 4
#define DEVICE_ID_MAX_LEN 63
#define DEVICE_ID_PADDED_LEN 64
#define TEMPERATURE_HEX_DIGITS 8
#define ACTIVE_FLAG_LEN 1

// Minimum buffer size: 4 (version) + 64 (device_id) + 8 (temperature) + 1 (active) = 77
#define MIN_BUFFER_SIZE (VERSION_HEX_DIGITS + DEVICE_ID_PADDED_LEN + TEMPERATURE_HEX_DIGITS + ACTIVE_FLAG_LEN)

// Temperature validation limits
#define TEMP_MIN -1000
#define TEMP_MAX 1000

// Version validation limits
#define VERSION_MIN 0
#define VERSION_MAX 65535

// Parse version (4 hex digits) from buffer
static bool parse_version(const char* p, int* out_version) {
    char version_str[VERSION_HEX_DIGITS + 1];
    memcpy(version_str, p, VERSION_HEX_DIGITS);
    version_str[VERSION_HEX_DIGITS] = '\0';
    
    char* endptr;
    errno = 0;
    long version = strtol(version_str, &endptr, 16);
    if (errno != 0 || *endptr != '\0' || version < VERSION_MIN || version > VERSION_MAX) {
        return false;
    }
    *out_version = (int)version;
    return true;
}

// Parse device_id (up to 63 chars, null-terminated) from buffer
static size_t parse_device_id(const char* p, char* out_device_id) {
    size_t id_len = 0;
    while (id_len < DEVICE_ID_MAX_LEN && p[id_len] != '\0' && p[id_len] != '|') {
        out_device_id[id_len] = p[id_len];
        id_len++;
    }
    out_device_id[id_len] = '\0';
    return id_len;
}

// Parse temperature (8 hex digits) from buffer
static bool parse_temperature(const char* p, int* out_temp) {
    char temp_str[TEMPERATURE_HEX_DIGITS + 1];
    memcpy(temp_str, p, TEMPERATURE_HEX_DIGITS);
    temp_str[TEMPERATURE_HEX_DIGITS] = '\0';
    
    char* endptr;
    errno = 0;
    long temp = strtol(temp_str, &endptr, 16);
    if (errno != 0 || *endptr != '\0') {
        return false;
    }
    *out_temp = (int)temp;
    return true;
}

// Parse active flag from buffer
static bool parse_active_flag(const char* p, bool* out_active) {
    if (p[0] == '1') {
        *out_active = true;
        return true;
    } else if (p[0] == '0') {
        *out_active = false;
        return true;
    }
    return false;
}

// Common parse function
bool protocol_common_parse(const char* buffer, size_t buffer_len, common_message* out) {
    if (buffer == NULL || out == NULL) {
        return false;
    }
    
    if (buffer_len < MIN_BUFFER_SIZE) {
        return false;
    }

    const char* p = buffer;

    // Parse version
    if (!parse_version(p, &out->version)) {
        return false;
    }
    p += VERSION_HEX_DIGITS;

    // Parse device_id (up to 63 chars, null-terminated)
    parse_device_id(p, out->device_id);
    p += DEVICE_ID_PADDED_LEN;

    // Parse temperature
    if (!parse_temperature(p, &out->temperature)) {
        return false;
    }
    p += TEMPERATURE_HEX_DIGITS;

    // Parse active flag
    if (!parse_active_flag(p, &out->active)) {
        return false;
    }
    
    return true;
}

// Common serialize function
int protocol_common_serialize(const common_message* msg, char* buffer, size_t buffer_size) {
    if (msg == NULL || buffer == NULL) {
        return -1;
    }
    
    if (buffer_size < MIN_BUFFER_SIZE) {
        return -1;
    }

    int written = 0;
    int result;

    // Serialize version
    result = snprintf(buffer + written, buffer_size - written, "%04X", msg->version);
    if (result < 0 || (size_t)result >= buffer_size - written) {
        return -1;
    }
    written += result;

    // Serialize device_id (pad to 64 bytes)
    size_t id_len = strlen(msg->device_id);
    if (id_len > DEVICE_ID_MAX_LEN) id_len = DEVICE_ID_MAX_LEN;
    memcpy(buffer + written, msg->device_id, id_len);
    // Zero-pad the rest
    memset(buffer + written + id_len, 0, DEVICE_ID_PADDED_LEN - id_len);
    written += DEVICE_ID_PADDED_LEN;

    // Serialize temperature
    result = snprintf(buffer + written, buffer_size - written, "%08X", (unsigned int)msg->temperature);
    if (result < 0 || (size_t)result >= buffer_size - written) {
        return -1;
    }
    written += result;

    // Serialize active flag
    if (written >= (int)buffer_size) {
        return -1;
    }
    buffer[written++] = msg->active ? '1' : '0';
    
    return written;
}

// Common validate function
bool protocol_common_validate(const common_message* msg) {
    if (msg == NULL) {
        return false;
    }
    
    if (msg->version < VERSION_MIN || msg->version > VERSION_MAX) {
        return false;
    }
    
    size_t id_len = strlen(msg->device_id);
    if (id_len == 0) {
        return false;
    }

    // Validate device_id characters (printable ASCII: 32-126)
    for (size_t i = 0; i < id_len; ++i) {
        if (msg->device_id[i] < 32 || msg->device_id[i] > 126) {
            return false;
        }
    }
    
    if (msg->temperature < TEMP_MIN || msg->temperature > TEMP_MAX) {
        return false;
    }
    
    return true;
}

// Common checksum function
unsigned int protocol_common_checksum(const common_message* msg) {
    if (msg == NULL) {
        return 0;
    }
    
    unsigned int sum = 0;
    
    sum += (unsigned int)msg->version;
    sum += (unsigned int)msg->temperature;
    sum += msg->active ? 1 : 0;

    size_t id_len = strlen(msg->device_id);
    for (size_t i = 0; i < id_len; ++i) {
        sum += (unsigned char)msg->device_id[i];
    }
    
    return sum;
}

