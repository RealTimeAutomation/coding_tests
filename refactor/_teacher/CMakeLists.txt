# Teacher-only final tests
# This CMakeLists.txt is included from the parent directory

# Final test executable (tests that catch bugs - will fail initially)
add_executable(run_tests_final
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/cunit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_metrics_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_text_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_config_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_list_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_string_utils_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_protocol_apple_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_protocol_banana_final.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_protocol_carrot_final.c
)
target_include_directories(run_tests_final PRIVATE ${CMAKE_SOURCE_DIR}/../_student/include ${CMAKE_SOURCE_DIR}/../_student/tests)
target_link_libraries(run_tests_final PRIVATE legacylib)
