cmake_minimum_required(VERSION 3.10)
project(legacy_refactor_answer_key C)

set(CMAKE_C_STANDARD 99)

# Library with all bug fixes
add_library(legacylib
    src/legacy/metrics.c
    src/legacy/text.c
    src/legacy/config.c
    src/legacy/list.c
    src/legacy/string_utils.c
    src/legacy/protocol_apple.c
    src/legacy/protocol_banana.c
    src/legacy/protocol_carrot.c
    src/logger.c
)
target_include_directories(legacylib PUBLIC include)

# Test executable (all tests should pass)
add_executable(run_tests
    tests/cunit.c
    tests/test_main.c
    tests/test_metrics.c
    tests/test_text.c
    tests/test_config.c
    tests/test_list.c
    tests/test_string_utils.c
    tests/test_protocol_apple.c
    tests/test_protocol_banana.c
    tests/test_protocol_carrot.c
)
target_include_directories(run_tests PRIVATE include tests)
target_link_libraries(run_tests PRIVATE legacylib)

# Final test executable (all tests should pass with fixed code)
add_executable(run_tests_final
    tests/cunit.c
    tests/test_main_final.c
    tests/test_metrics_final.c
    tests/test_text_final.c
    tests/test_config_final.c
    tests/test_list_final.c
    tests/test_string_utils_final.c
    tests/test_protocol_apple_final.c
    tests/test_protocol_banana_final.c
    tests/test_protocol_carrot_final.c
)
target_include_directories(run_tests_final PRIVATE include tests)
target_link_libraries(run_tests_final PRIVATE legacylib)

# Main executable
add_executable(main
    src/main.c
)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE legacylib)

enable_testing()
add_test(NAME run_all COMMAND run_tests)
add_test(NAME run_all_final COMMAND run_tests_final)

