#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LOG_NONE = 0,
    LOG_ERROR = 1,
    LOG_WARN = 2,
    LOG_INFO = 3,
    LOG_DEBUG = 4
} log_level_t;

// Initialize logger with level from environment variable LOG_LEVEL or default
void logger_init(void);

// Set log level programmatically
void logger_set_level(log_level_t level);

// Get current log level
log_level_t logger_get_level(void);

// Log functions
void log_error(const char* format, ...);
void log_warn(const char* format, ...);
void log_info(const char* format, ...);
void log_debug(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // LOGGER_H

