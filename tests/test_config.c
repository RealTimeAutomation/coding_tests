#include "cunit.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

CUNIT_TEST(test_parse_basic) {
    const char* path = "tests_tmp.cfg";
    const char* data =
        "# sample\n"
        "host = example.com\n"
        "port=8080\n"
        "enable_tls=true\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);

    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_EQ(cfg.port, 8080);
    CUNIT_ASSERT(cfg.enable_tls == true);
    CUNIT_ASSERT_STR_EQ(cfg.host, "example.com");
}

CUNIT_TEST(test_parse_no_spaces) {
    const char* path = "tests_tmp2.cfg";
    const char* data = "host=test.com\nport=9000\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);

    CUNIT_ASSERT(ok);
    CUNIT_ASSERT_STR_EQ(cfg.host, "test.com");
    CUNIT_ASSERT_EQ(cfg.port, 9000);
}

CUNIT_TEST(test_parse_false) {
    const char* path = "tests_tmp3.cfg";
    const char* data = "enable_tls=false\n";
    FILE* f = fopen(path, "wb");
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    app_config cfg;
    bool ok = config_parse_file(path, &cfg);
    remove(path);

    CUNIT_ASSERT(ok);
    CUNIT_ASSERT(cfg.enable_tls == false);
}

// Intentionally skipping tests for: uppercase TRUE/FALSE, long lines (>255), invalid keys, host overflow, NULL pointers

