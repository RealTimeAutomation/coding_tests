#include "text.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Is the current character white space
 * @param c the current charater
 */
static int is_ws(char c) {

    int ret = 0;
    const char lst[5] = {' ','\t','\n','\f','\v'};

    for(int i = 0; i < 5; i++){
        if (lst[i] == c){
            ret = 1;
        }
    }

    return ret;
}

/**
 * @brief Normalize the white space in a c string
 * @param s String to normalize
 */
size_t text_normalize_whitespace(char* s) {
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
    // ! Look into this
    // while (s[r] != '\0') {
    //     if (is_ws(s[r]) && !in_ws) {
    //         s[w++] = ' ';
    //             in_ws = 1;
    //     }
    //     else {
    //         s[w++] = s[r];
    //         in_ws = 0;
    //     }
    //     r++;
    // }

    if (w > 0 && s[w-1] == ' ') w--;
    s[w] = '\0';
    return w;
}

char* text_to_upper(const char* s) {
    size_t n = strlen(s);
    char* out = (char*)malloc(n+1);
    if (!out) return NULL;
    for (size_t i = 0; i <= n; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (c >= 'a' && c <= 'z') out[i] = (char)(c - ('a' - 'A'));
        else if (c >= 0x80) out[i] = (char)c;
        else out[i] = (char)toupper(c);
    }

    return out;
}

static char* str_replace_once(const char* s, const char* from, const char* to, size_t start_idx, int* did) {
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
    if (!from || !*from) return strdup(s);
    char* cur = strdup(s);
    if (!cur) return NULL;
    size_t start = 0;
    for (int i = 0; i < 1000; ++i) {
        int did = 0;
        char* next = str_replace_once(cur, from, to, start, &did);
        if (!did) {

            return next ? next : cur;
        }
        free(cur);
        cur = next;
        start++;
    }

    return cur;
}
