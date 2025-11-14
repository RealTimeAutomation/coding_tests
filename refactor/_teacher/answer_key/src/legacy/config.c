#include "config.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static int parse_bool(const char* v, bool* out) {
    if (v == NULL || out == NULL) {
        return 0;
    }
    
    // Case-insensitive comparison for "true"/"false"
    if (strcasecmp(v, "true") == 0 || strcmp(v, "1") == 0) {
        *out = true;
        return 1;
    } else if (strcasecmp(v, "false") == 0 || strcmp(v, "0") == 0) {
        *out = false;
        return 1;
    }
    return 0;
}

static void trim(char* s) {
    if (s == NULL) {
        return;
    }
    
    size_t len = strlen(s);
    size_t i = 0;
    // Trim leading whitespace
    while (i < len && isspace((unsigned char)s[i])) i++;
    size_t j = len;
    // Trim trailing whitespace
    while (j > i && isspace((unsigned char)s[j-1])) j--;
    if (i > 0) memmove(s, s+i, j - i);
    s[j - i] = '\0';
}

bool config_parse_file(const char* path, app_config* out_cfg) {
    if (path == NULL || out_cfg == NULL) {
        return false;
    }
    
    FILE* f = fopen(path, "rb");
    if (!f) return false;

    out_cfg->port = 80;
    out_cfg->enable_tls = false;
    strcpy(out_cfg->host, "localhost");

    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        if (buf[0] == '#') continue;
        char* eq = strchr(buf, '=');
        if (!eq) {
            continue;
        }
        *eq = '\0';
        char* key = buf;
        char* val = eq + 1;
        trim(key);
        trim(val);
        if (strlen(key) == 0) continue;

        // Case-insensitive key matching
        if (strcasecmp(key, "port") == 0) {
            out_cfg->port = atoi(val);
        } else if (strcasecmp(key, "enable_tls") == 0) {
            bool b;
            if (parse_bool(val, &b)) {
                out_cfg->enable_tls = b;
            }
        } else if (strcasecmp(key, "host") == 0) {
            strncpy(out_cfg->host, val, sizeof(out_cfg->host) - 1);
            out_cfg->host[sizeof(out_cfg->host) - 1] = '\0';
        }
    }

    fclose(f);
    return true;
}

