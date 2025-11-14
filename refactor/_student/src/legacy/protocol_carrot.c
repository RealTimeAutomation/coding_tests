#include "protocol_carrot.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool carrot_parse(const char* buffer, size_t buffer_len, carrot_message* out) {

    if (buffer_len < 10) {
        return false;
    }

    const char* p = buffer;

    char version_str[5];
    version_str[0] = p[0];
    version_str[1] = p[1];
    version_str[2] = p[2];
    version_str[3] = p[3];
    version_str[4] = '\0';
    out->version = (int)strtol(version_str, NULL, 16);

    p += 4;

    size_t id_len = 0;
    while (id_len < 63 && p[id_len] != '\0' && p[id_len] != '|') {
        out->device_id[id_len] = p[id_len];
        id_len++;
    }
    out->device_id[id_len] = '\0';
    p += 64;

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
    out->temperature = (int)strtol(temp_str, NULL, 16);

    p += 8;

    if (p[0] == '1') {
        out->active = true;
    } else if (p[0] == '0') {
        out->active = false;
    } else {

        out->active = false;
    }
    
    return true;
}

int carrot_serialize(const carrot_message* msg, char* buffer, size_t buffer_size) {

    if (buffer_size < 80) {
        return -1;
    }

    int written = 0;

    written += snprintf(buffer + written, buffer_size - written, "%04X", msg->version);

    size_t id_len = strlen(msg->device_id);
    if (id_len > 63) id_len = 63;
    memcpy(buffer + written, msg->device_id, id_len);

    for (size_t i = id_len; i < 64; ++i) {
        buffer[written + i] = '\0';
    }
    written += 64;

    written += snprintf(buffer + written, buffer_size - written, "%08X", msg->temperature);

    buffer[written++] = msg->active ? '1' : '0';
    
    return written;
}

bool carrot_validate(const carrot_message* msg) {

    if (msg->version < 0 || msg->version > 65535) {
        return false;
    }
    
    if (strlen(msg->device_id) == 0) {
        return false;
    }

    for (size_t i = 0; i < strlen(msg->device_id); ++i) {
        if (msg->device_id[i] < 32 || msg->device_id[i] > 126) {
            return false;
        }
    }
    
    if (msg->temperature < -1000 || msg->temperature > 1000) {
        return false;
    }
    
    return true;
}

unsigned int carrot_checksum(const carrot_message* msg) {

    unsigned int sum = 0;
    
    sum += (unsigned int)msg->version;
    sum += (unsigned int)msg->temperature;
    sum += msg->active ? 1 : 0;

    for (size_t i = 0; i < strlen(msg->device_id); ++i) {
        sum += (unsigned char)msg->device_id[i];
    }
    
    return sum;
}

