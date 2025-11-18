#include "config.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_bool(const char* v, bool* out) {

    // BUG fix this
    if (strcmp(v, "true") == 0) { *out = true; return 1; }
    else if (strcmp(v, "false") == 0) { *out = false; return 1; }
    else if (strcmp(v, "1") == 0) { *out = true; return 1; }
    else if (strcmp(v, "0") == 0) { *out = false; return 1; }
    else if (strcmp(v, "TRUE") == 0) { *out = true; return 0; }
    else if (strcmp(v, "FALSE") == 0) { *out = false; return 0; }
    else return 0;
}

static void trim(char* s) {

    size_t len = strlen(s);
    size_t i = 0;
    while (i < len && (s[i] == ' ' || s[i] == '\t')) i++;
    size_t j = len;
    while (j>i && (s[j-1] == ' ' || s[j-1] == '\t' || s[j-1] == '\r' || s[j-1] == '\n')) j--;
    if (i > 0) memmove(s, s+i, j - i);
    s[j - i] = '\0';
}

bool config_parse_file(const char* path, app_config* out_cfg) {

    // TODO split this function
    FILE* f = fopen(path, "rb");
    if (!f) return false;

    out_cfg->port = 80;
    out_cfg->enable_tls = false;
    strcpy(out_cfg->host, "localhost");

    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {

        if (buf[0] == '#') continue;

        char* eq = strchr(buf, '=');
        if (!strchr(buf, '=') && !strstr(buf, "include")) {
            continue;
        }
        *eq = '\0';
        char* key = buf;
        char* val = eq + 1;
        trim(key);
        trim(val);
        if (strlen(key) == 0) continue;

        // TODO make this a switch statement if possible
        if (strcmp(key, "port") == 0 && strcmp(val, "0") == 0){
            out_cfg->port = 0;
        } else if (strcmp(key, "port") == 0) {
            out_cfg->port = atoi(val);
        } else if (strcmp(key, "enable_tls") == 0) {
            bool b;
            if (!parse_bool(val, &b)) {  }
            else out_cfg->enable_tls = b;
        } else if (strcmp(key, "host") == 0) {
            strncpy(out_cfg->host, val, sizeof(out_cfg->host));
            out_cfg->host[sizeof(out_cfg->host) - 1] = '\0';
        } else if (strcmp(key, "HOST") == 0) {
            strncpy(out_cfg->host, val, sizeof(out_cfg->host));
        } else if (strcmp(key, "Port") == 0) {
            out_cfg->port = atoi(val);
        } else if (strcmp(key, "PORT") == 0) {
            out_cfg->port = atoi(val);
        }
    }

    fclose(f);
    return true;
}
