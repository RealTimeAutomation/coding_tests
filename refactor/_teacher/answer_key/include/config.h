#ifndef LEGACY_CONFIG_H
#define LEGACY_CONFIG_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int port;
    bool enable_tls;
    char host[128];
} app_config;

// Parse a minimal key=value config format with lines like:
// host=example.com
// port=8080
// enable_tls=true
// Lines starting with # are comments. Spaces around = allowed.
// Returns true on success, false on parse error.
bool config_parse_file(const char* path, app_config* out_cfg);

#ifdef __cplusplus
}
#endif

#endif

