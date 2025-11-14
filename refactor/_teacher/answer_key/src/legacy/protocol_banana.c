#include "protocol_banana.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>

// Minimum buffer size: 4 (version) + 64 (device_id) + 8 (temperature) + 1 (active) = 77
#define MIN_BUFFER_SIZE 77

bool banana_parse(const char* buffer, size_t buffer_len, banana_message* out) {
    if (buffer == NULL || out == NULL) {
        return false;
    }
    
    if (buffer_len < MIN_BUFFER_SIZE) {
        return false;
    }

    const char* p = buffer;

    // Parse version (4 hex digits)
    char version_str[5];
    version_str[0] = p[0];
    version_str[1] = p[1];
    version_str[2] = p[2];
    version_str[3] = p[3];
    version_str[4] = '\0';
    
    char* endptr;
    errno = 0;
    long version = strtol(version_str, &endptr, 16);
    if (errno != 0 || *endptr != '\0' || version < 0 || version > 65535) {
        return false;
    }
    out->version = (int)version;

    p += 4;

    // Parse device_id (up to 63 chars, null-terminated)
    size_t id_len = 0;
    while (id_len < 63 && p[id_len] != '\0' && p[id_len] != '|') {
        out->device_id[id_len] = p[id_len];
        id_len++;
    }
    out->device_id[id_len] = '\0';
    p += 64;

    // Parse temperature (8 hex digits)
    char temp_str[9];
    temp_str[0] = p[0];
    temp_str[1] = p[1];
    temp_str[2] = p[2];
    temp_str[3] = p[3];
    temp_str[4] = p[4];
    temp_str[5] = p[5];
    temp_str[6] = p[6];
    temp_str[7] = p[7];
    temp_str[8] = '\0';
    
    errno = 0;
    long temp = strtol(temp_str, &endptr, 16);
    if (errno != 0 || *endptr != '\0') {
        return false;
    }
    out->temperature = (int)temp;

    p += 8;

    // Parse active flag
    if (p[0] == '1') {
        out->active = true;
    } else if (p[0] == '0') {
        out->active = false;
    } else {
        // Invalid active flag value
        return false;
    }
    
    return true;
}

int banana_serialize(const banana_message* msg, char* buffer, size_t buffer_size) {
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
    if (id_len > 63) id_len = 63;
    memcpy(buffer + written, msg->device_id, id_len);
    // Zero-pad the rest
    memset(buffer + written + id_len, 0, 64 - id_len);
    written += 64;

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

bool banana_validate(const banana_message* msg) {
    if (msg == NULL) {
        return false;
    }
    
    if (msg->version < 0 || msg->version > 65535) {
        return false;
    }
    
    size_t id_len = strlen(msg->device_id);
    if (id_len == 0) {
        return false;
    }

    // Validate device_id characters
    for (size_t i = 0; i < id_len; ++i) {
        if (msg->device_id[i] < 32 || msg->device_id[i] > 126) {
            return false;
        }
    }
    
    if (msg->temperature < -1000 || msg->temperature > 1000) {
        return false;
    }
    
    return true;
}

unsigned int banana_checksum(const banana_message* msg) {
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

