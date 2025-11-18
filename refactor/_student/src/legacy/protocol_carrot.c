#include "protocol_carrot.h"
#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Private function to convert carrot message to generic message
 * @param src Source carrot message
 * @param dest Destination generic message
 */
static void conv_carrot_generic(const carrot_message* src, gen_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}

/**
 * @brief Private function to convert generic message to carrot message
 * @param src Source generic message
 * @param dest Destination carrot message
 */
static void conv_generic_carrot(const gen_message* src, carrot_message* dest){
    dest->version = src->version;
    strcpy(dest->device_id,src->device_id);
    dest->temperature = src->temperature;
    dest->active = src->active;
}

bool carrot_parse(const char* buffer, size_t buffer_len, carrot_message* out) {

    // [x] added null pointer check
    if(out == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    bool ret = gen_parse(buffer, buffer_len, &gen_msg);
    conv_generic_carrot(&gen_msg, out);
    return ret;
}

int carrot_serialize(const carrot_message* msg, char* buffer, size_t buffer_size) {

    // [x] added null pointer check
    if(msg == NULL){
        return -1;
    }
    gen_message gen_msg = {};
    conv_carrot_generic(msg, &gen_msg);
    return gen_serialize(&gen_msg, buffer, buffer_size);

}

bool carrot_validate(const carrot_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_carrot_generic(msg, &gen_msg);
    return gen_validate(&gen_msg);

}

unsigned int carrot_checksum(const carrot_message* msg) {

    // [x] added null pointer check
    if(msg == NULL){
        return 0;
    }
    gen_message gen_msg = {};
    conv_carrot_generic(msg, &gen_msg);
    return gen_checksum(&gen_msg);

}

