#include "text.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Use standard library function for whitespace detection
#define is_ws(c) isspace((unsigned char)(c))

size_t text_normalize_whitespace(char* s) {
    if (s == NULL) {
        return 0;
    }
    
    size_t r = 0, w = 0;
    int in_ws = 1;
    while (s[r] != '\0') {
        if (is_ws(s[r])) {
            if (!in_ws) {
                s[w++] = ' ';
                in_ws = 1;
            }
        } else {
            s[w++] = s[r];
            in_ws = 0;
        }
        r++;
    }

    if (w > 0 && s[w-1] == ' ') w--;
    s[w] = '\0';
    return w;
}

char* text_to_upper(const char* s) {
    if (s == NULL) {
        return NULL;
    }
    
    size_t n = strlen(s);
    char* out = (char*)malloc(n+1);
    if (!out) return NULL;
    for (size_t i = 0; i < n; ++i) {
        out[i] = (char)toupper((unsigned char)s[i]);
    }
    out[n] = '\0';
    return out;
}

static char* str_replace_once(const char* s, const char* from, const char* to, size_t start_idx, int* did) {
    if (s == NULL || from == NULL || to == NULL) {
        *did = 0;
        return NULL;
    }
    
    const char* p = strstr(s + start_idx, from);
    *did = 0;
    if (!p) return NULL;
    *did = 1;
    size_t prefix = (size_t)(p - s);
    size_t from_len = strlen(from);
    size_t to_len = strlen(to);
    size_t s_len = strlen(s);
    char* out = (char*)malloc(s_len - from_len + to_len + 1);
    if (!out) return NULL;
    memcpy(out, s, prefix);
    memcpy(out + prefix, to, to_len);
    memcpy(out + prefix + to_len, p + from_len, s_len - prefix - from_len + 1);
    return out;
}

char* text_replace_all(const char* s, const char* from, const char* to) {
    if (s == NULL) {
        return NULL;
    }
    
    if (!from || !*from) return strdup(s);
    char* cur = strdup(s);
    if (!cur) return NULL;
    size_t start = 0;
    // Limit iterations to prevent infinite loops (safety limit)
    const int MAX_REPLACEMENT_ITERATIONS = 1000;
    for (int i = 0; i < MAX_REPLACEMENT_ITERATIONS; ++i) {
        int did = 0;
        char* next = str_replace_once(cur, from, to, start, &did);
        if (!did) {
            if (next) {
                free(cur);
                return next;
            }
            return cur;
        }
        if (next == NULL) {
            free(cur);
            return NULL;
        }
        free(cur);
        cur = next;
        start = 0; // Reset start after each replacement
    }

    return cur;
}

