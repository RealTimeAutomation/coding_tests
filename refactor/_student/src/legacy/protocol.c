#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool gen_parse(const char* buffer, size_t buffer_len, gen_message* out) {

    if (buffer_len < 10) {
        return false;
    }

    char version_str[5];
    strncpy(version_str, buffer, sizeof(version_str)-1);
    version_str[4] = '\0';
    out->version = (int)strtol(version_str, NULL, 16);
    
    buffer += 4;

    size_t id_len = 0;
    while (id_len < 63 && buffer[id_len] != '\0' && buffer[id_len] != '|') {
        out->device_id[id_len] = buffer[id_len];
        id_len++;
    }
    out->device_id[id_len] = '\0';
    buffer += 64;

    char temp_str[9];
    strncpy(temp_str, buffer, sizeof(temp_str)-1);
    temp_str[8] = '\0';
    out->temperature = (int)strtol(temp_str, NULL, 16);

    buffer += 8;

    if (buffer[0] == '1') {
        out->active = true;
    } else if (buffer[0] == '0') {
        out->active = false;
    } else {

        out->active = false;
    }
    
    return true;
}

int gen_serialize(const gen_message* msg, char* buffer, size_t buffer_size) {

    // Return -1 if msg is NULL, buffer is NULL, or buffer_size < 77
    if (buffer_size < 77 || !buffer || !msg) {
        return -1;
    }

    int written = 0;

    // TODO This needs investigating

    // Write message version to buffer starting at next available position, with a maximum capacity of the buffer size - any currently taken slots
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

bool gen_validate(const gen_message* msg) {

    if(!msg){
        return false;
    }

    bool ret = true;

    if (msg->version < 0 || msg->version > 65535) {
        ret = false;
    }
    
    if (strlen(msg->device_id) == 0) {
        ret = false;
    }

    for (size_t i = 0; i < strlen(msg->device_id); ++i) {
        if (msg->device_id[i] < 32 || msg->device_id[i] > 126) {
            ret = false;
        }
    }
    
    if (msg->temperature < -1000 || msg->temperature > 1000) {
        ret = false;
    }
    
    return ret;
}

unsigned int gen_checksum(const gen_message* msg) {

    if(!msg){
        return 0;
    }

    unsigned int sum = 0;
    
    sum += (unsigned int)msg->version;
    sum += (unsigned int)msg->temperature;
    sum += msg->active ? 1 : 0;

    for (size_t i = 0; i < strlen(msg->device_id); ++i) {
        sum += (unsigned char)msg->device_id[i];
    }
    
    return sum;
}

