cmake_minimum_required(VERSION 3.10)
project(legacy_refactor_project C)

set(CMAKE_C_STANDARD 99)

# Library
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

# Test executable
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

# Main executable
add_executable(main
    src/main.c
)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE legacylib)

# Final tests are in _teacher/ directory (teacher-only, should be deleted before distribution)

enable_testing()
add_test(NAME run_all COMMAND run_tests)

# Include teacher tests if _teacher directory exists (teacher-only, delete before distribution)
if(EXISTS "${CMAKE_SOURCE_DIR}/_teacher/CMakeLists.txt")
    add_subdirectory(_teacher)
    add_test(NAME run_all_final COMMAND run_tests_final)
endif()
