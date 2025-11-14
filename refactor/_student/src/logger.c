#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static log_level_t current_level = LOG_WARN;

static const char* level_names[] = {
    "NONE",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG"
};

static log_level_t parse_log_level(const char* level_str) {
    if (level_str == NULL) {
        return LOG_WARN;
    }
    
    if (strcmp(level_str, "NONE") == 0 || strcmp(level_str, "none") == 0) {
        return LOG_NONE;
    } else if (strcmp(level_str, "ERROR") == 0 || strcmp(level_str, "error") == 0) {
        return LOG_ERROR;
    } else if (strcmp(level_str, "WARN") == 0 || strcmp(level_str, "warn") == 0) {
        return LOG_WARN;
    } else if (strcmp(level_str, "INFO") == 0 || strcmp(level_str, "info") == 0) {
        return LOG_INFO;
    } else if (strcmp(level_str, "DEBUG") == 0 || strcmp(level_str, "debug") == 0) {
        return LOG_DEBUG;
    }
    
    return LOG_WARN;
}

void logger_init(void) {
    const char* env_level = getenv("LOG_LEVEL");
    current_level = parse_log_level(env_level);
}

void logger_set_level(log_level_t level) {
    if (level >= LOG_NONE && level <= LOG_DEBUG) {
        current_level = level;
    }
}

log_level_t logger_get_level(void) {
    return current_level;
}

static void log_message(log_level_t level, const char* format, va_list args) {
    // Don't log if level is NONE or if level exceeds current level
    if (level == LOG_NONE || level > current_level) {
        return;
    }
    
    fprintf(stderr, "[%s] ", level_names[level]);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_ERROR, format, args);
    va_end(args);
}

void log_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_WARN, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_INFO, format, args);
    va_end(args);
}

void log_debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_DEBUG, format, args);
    va_end(args);
}

