/**
 * @file config.h
 * @brief Configuration file parsing
 * 
 * This module provides functionality to parse simple key=value configuration
 * files with support for comments and whitespace handling.
 */

#ifndef LEGACY_CONFIG_H
#define LEGACY_CONFIG_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Application configuration structure
 */
typedef struct {
    int port;           /**< Port number (default: 80) */
    bool enable_tls;    /**< TLS/SSL enabled flag (default: false) */
    char host[128];     /**< Hostname or IP address (default: "localhost") */
} app_config;

/**
 * @brief Parses a configuration file and populates a config structure
 * 
 * Parses a simple key=value format configuration file. Supports:
 * - Comments: Lines starting with '#' are ignored
 * - Whitespace: Spaces around '=' and key/value are trimmed
 * - Keys: "port", "enable_tls", "host" (case-insensitive)
 * - Values: 
 *   - port: Integer (parsed with atoi)
 *   - enable_tls: Boolean (true/false, TRUE/FALSE, 1/0, case-insensitive)
 *   - host: String (max 127 characters, null-terminated)
 * 
 * @param path Path to the configuration file (can be NULL)
 * @param out_cfg Pointer to config structure to populate (can be NULL)
 * @return true if parsing succeeded, false on error
 * 
 * @note Returns false if path or out_cfg is NULL, or if file cannot be opened
 * @note Default values are set before parsing: port=80, enable_tls=false, host="localhost"
 * @note Invalid keys are silently ignored
 * @note Long lines (>255 chars) may cause undefined behavior
 * 
 * @example
 *   app_config cfg;
 *   if (config_parse_file("config.cfg", &cfg)) {
 *       // Use cfg.port, cfg.enable_tls, cfg.host
 *   }
 * 
 * Config file format:
 *   # This is a comment
 *   host = example.com
 *   port=8080
 *   enable_tls=true
 */
bool config_parse_file(const char* path, app_config* out_cfg);

#ifdef __cplusplus
}
#endif

#endif

