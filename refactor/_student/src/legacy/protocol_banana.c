#include "protocol_banana.h"
#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Private function to convert banana message to generic message
 * @param src Source banana message
 * @param dest Destination generic message
 */
static void conv_banana_generic(const banana_message* src, gen_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}

/**
 * @brief Private function to convert generic message to banana message
 * @param src Source generic message
 * @param dest Destination banana message
 */
static void conv_generic_banana(const gen_message* src, banana_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}


bool banana_parse(const char* buffer, size_t buffer_len, banana_message* out) {

    // [x] added null pointer check
    if(out == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    bool ret = gen_parse(buffer, buffer_len, &gen_msg);
    conv_generic_banana(&gen_msg, out);
    return ret;
}

int banana_serialize(const banana_message* msg, char* buffer, size_t buffer_size) {

    // [x] added null pointer check
    if(msg == NULL){
        return -1;
    }
    gen_message gen_msg = {};
    conv_banana_generic(msg, &gen_msg);
    return gen_serialize(&gen_msg, buffer, buffer_size);

}

bool banana_validate(const banana_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_banana_generic(msg, &gen_msg);
    return gen_validate(&gen_msg);

}

unsigned int banana_checksum(const banana_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_banana_generic(msg, &gen_msg);
    return gen_checksum(&gen_msg);

}

