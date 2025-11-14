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
    
    if (strcmp(v, "true") == 0) { *out = true; return 1; }
    else if (strcmp(v, "false") == 0) { *out = false; return 1; }
    else if (strcmp(v, "1") == 0) { *out = true; return 1; }
    else if (strcmp(v, "0") == 0) { *out = false; return 1; }
    else if (strcmp(v, "TRUE") == 0) { *out = true; return 1; }
    else if (strcmp(v, "FALSE") == 0) { *out = false; return 1; }
    else return 0;
}

static void trim(char* s) {
    if (s == NULL) {
        return;
    }
    
    size_t len = strlen(s);
    size_t i = 0;
    while (i < len && (s[i] == ' ' || s[i] == '\t')) i++;
    size_t j = len;
    while (j>i && (s[j-1] == ' ' || s[j-1] == '\t' || s[j-1] == '\r' || s[j-1] == '\n')) j--;
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

