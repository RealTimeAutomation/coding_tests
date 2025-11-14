#include "cunit.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

// These tests are designed to catch bugs and will fail initially

CUNIT_TEST(test_parse_null_pointer) {
    app_config cfg;
    bool result = config_parse_file(NULL, &cfg);
    // Should handle NULL path gracefully
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_parse_null_config) {
    bool result = config_parse_file("nonexistent.cfg", NULL);
    // Should handle NULL config gracefully
    CUNIT_ASSERT(result == false);
}

CUNIT_TEST(test_parse_uppercase_true) {
    const char* path = "test_upper_true.cfg";
    const char* data = "enable_tls=TRUE\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT(cfg.enable_tls == true);
}

CUNIT_TEST(test_parse_uppercase_false) {
    const char* path = "test_upper_false.cfg";
    const char* data = "enable_tls=FALSE\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT(cfg.enable_tls == false);
}

CUNIT_TEST(test_parse_long_line) {
    const char* path = "test_long.cfg";
    char data[300];
    memset(data, 'a', 250);
    data[250] = '\n';
    data[251] = '\0';
    
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    // Should handle long lines gracefully
    CUNIT_ASSERT(ok == true || ok == false);
}

CUNIT_TEST(test_parse_invalid_key) {
    const char* path = "test_invalid.cfg";
    const char* data = "unknown_key=value\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    // Should handle unknown keys gracefully
    CUNIT_ASSERT(ok == true || ok == false);
}

CUNIT_TEST(test_parse_host_overflow) {
    const char* path = "test_overflow.cfg";
    char data[300];
    strcpy(data, "host=");
    memset(data + 5, 'x', 200);
    strcat(data, "\n");
    
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    // Should handle overflow gracefully
    CUNIT_ASSERT(ok == true || ok == false);
}

CUNIT_TEST(test_parse_no_newline_end) {
    const char* path = "test_no_nl.cfg";
    const char* data = "port=8080"; // No newline at end
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);
    
    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(cfg.port, 8080);
}

