/**
 * @file logger.h
 * @brief Logging system with configurable levels
 * 
 * This module provides a simple logging system with multiple severity levels.
 * Log level can be configured via environment variable or programmatically.
 * All log output goes to stderr.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log severity levels (in ascending order)
 */
typedef enum {
    LOG_NONE = 0,   /**< No logging */
    LOG_ERROR = 1,  /**< Error messages only */
    LOG_WARN = 2,    /**< Warnings and errors */
    LOG_INFO = 3,    /**< Informational messages, warnings, and errors */
    LOG_DEBUG = 4    /**< All messages including debug */
} log_level_t;

/**
 * @brief Initializes the logger system
 * 
 * Reads the LOG_LEVEL environment variable and sets the log level accordingly.
 * If LOG_LEVEL is not set or invalid, defaults to LOG_WARN.
 * 
 * @note Should be called once at program startup
 * @note Supports case-insensitive level names: NONE, ERROR, WARN, INFO, DEBUG
 * 
 * @example
 *   logger_init(); // Reads LOG_LEVEL from environment
 */
void logger_init(void);

/**
 * @brief Sets the log level programmatically
 * 
 * @param level Log level to set (LOG_NONE through LOG_DEBUG)
 * 
 * @note Only sets level if it's in valid range (LOG_NONE <= level <= LOG_DEBUG)
 * @note Overrides environment variable setting
 * 
 * @example
 *   logger_set_level(LOG_INFO);
 */
void logger_set_level(log_level_t level);

/**
 * @brief Gets the current log level
 * 
 * @return Current log level
 * 
 * @example
 *   log_level_t level = logger_get_level();
 */
log_level_t logger_get_level(void);

/**
 * @brief Logs an error message
 * 
 * @param format printf-style format string
 * @param ... Variable arguments for format string
 * 
 * @note Only logs if current level >= LOG_ERROR
 * @note Output format: "[ERROR] <message>\n"
 * 
 * @example
 *   log_error("Failed to open file: %s", filename);
 */
void log_error(const char* format, ...);

/**
 * @brief Logs a warning message
 * 
 * @param format printf-style format string
 * @param ... Variable arguments for format string
 * 
 * @note Only logs if current level >= LOG_WARN
 * @note Output format: "[WARN] <message>\n"
 * 
 * @example
 *   log_warn("Deprecated function used");
 */
void log_warn(const char* format, ...);

/**
 * @brief Logs an informational message
 * 
 * @param format printf-style format string
 * @param ... Variable arguments for format string
 * 
 * @note Only logs if current level >= LOG_INFO
 * @note Output format: "[INFO] <message>\n"
 * 
 * @example
 *   log_info("Server started on port %d", port);
 */
void log_info(const char* format, ...);

/**
 * @brief Logs a debug message
 * 
 * @param format printf-style format string
 * @param ... Variable arguments for format string
 * 
 * @note Only logs if current level >= LOG_DEBUG
 * @note Output format: "[DEBUG] <message>\n"
 * 
 * @example
 *   log_debug("Processing item %d of %d", current, total);
 */
void log_debug(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif

