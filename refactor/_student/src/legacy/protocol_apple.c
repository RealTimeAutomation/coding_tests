#include "protocol_apple.h"
#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Private function to convert apple message to generic message
 * @param src Source apple message
 * @param dest Destination generic message
 */
static void conv_apple_generic(const apple_message* src, gen_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}

/**
 * @brief Private function to convert generic message to apple message
 * @param src Source generic message
 * @param dest Destination apple message
 */
static void conv_generic_apple(const gen_message* src, apple_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}

bool apple_parse(const char* buffer, size_t buffer_len, apple_message* out) {

    // [x] added null pointer check
    if(out == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    bool ret = gen_parse(buffer, buffer_len, &gen_msg);
    conv_generic_apple(&gen_msg, out);
    return ret;

}

int apple_serialize(const apple_message* msg, char* buffer, size_t buffer_size) {

    // [x] added null pointer check
    if(msg == NULL){
        return -1;
    }
    gen_message gen_msg = {};
    conv_apple_generic(msg, &gen_msg);
    return gen_serialize(&gen_msg, buffer, buffer_size);

}

bool apple_validate(const apple_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_apple_generic(msg, &gen_msg);
    return gen_validate(&gen_msg);

}

unsigned int apple_checksum(const apple_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_apple_generic(msg, &gen_msg);
    return gen_checksum(&gen_msg);

}

