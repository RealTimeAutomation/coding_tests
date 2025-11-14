#include "protocol_carrot.h"
#include "legacy/protocol_common.h"
#include <string.h>

// Since carrot_message and common_message have identical layouts, we can safely cast
bool carrot_parse(const char* buffer, size_t buffer_len, carrot_message* out) {
    if (out == NULL) {
        return false;
    }
    // Cast to common_message since layouts are identical
    return protocol_common_parse(buffer, buffer_len, (common_message*)out);
}

int carrot_serialize(const carrot_message* msg, char* buffer, size_t buffer_size) {
    if (msg == NULL) {
        return -1;
    }
    // Cast to common_message since layouts are identical
    return protocol_common_serialize((const common_message*)msg, buffer, buffer_size);
}

bool carrot_validate(const carrot_message* msg) {
    if (msg == NULL) {
        return false;
    }
    // Cast to common_message since layouts are identical
    return protocol_common_validate((const common_message*)msg);
}

unsigned int carrot_checksum(const carrot_message* msg) {
    if (msg == NULL) {
        return 0;
    }
    // Cast to common_message since layouts are identical
    return protocol_common_checksum((const common_message*)msg);
}

