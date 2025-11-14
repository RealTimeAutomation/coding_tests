#ifndef CUNIT_H
#define CUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

extern jmp_buf __cunit_jmp_env;
extern const char* __cunit_fail_msg;
extern const char* __cunit_fail_file;
extern int __cunit_fail_line;

typedef struct {
    const char* name;
    void (*func)(void);
} test_case_t;

extern test_case_t* __cunit_tests;
extern int __cunit_test_count;
extern int __cunit_test_capacity;

#define CUNIT_TEST(test_func_name) \
    void test_func_name(void); \
    void __cunit_register_##test_func_name(void) __attribute__((constructor)); \
    void __cunit_register_##test_func_name(void) { \
        extern test_case_t* __cunit_tests; \
        extern int __cunit_test_count; \
        extern int __cunit_test_capacity; \
        const char* test_name_str = #test_func_name; \
        if (__cunit_tests == NULL) { \
            __cunit_test_capacity = 32; \
            __cunit_tests = (test_case_t*)malloc(__cunit_test_capacity * sizeof(test_case_t)); \
        } \
        if (__cunit_test_count >= __cunit_test_capacity) { \
            __cunit_test_capacity *= 2; \
            __cunit_tests = (test_case_t*)realloc(__cunit_tests, __cunit_test_capacity * sizeof(test_case_t)); \
        } \
        __cunit_tests[__cunit_test_count].name = test_name_str; \
        __cunit_tests[__cunit_test_count].func = test_func_name; \
        __cunit_test_count++; \
    } \
    void test_func_name(void)

#define CUNIT_ASSERT(cond) do { \
    extern const char* __cunit_fail_file; \
    extern int __cunit_fail_line; \
    extern const char* __cunit_fail_msg; \
    extern jmp_buf __cunit_jmp_env; \
    if (!(cond)) { \
        __cunit_fail_file = __FILE__; \
        __cunit_fail_line = __LINE__; \
        __cunit_fail_msg = "Assertion failed: " #cond; \
        longjmp(__cunit_jmp_env, 1); \
    } \
} while(0)

#define CUNIT_ASSERT_EQ(a, b) do { \
    extern const char* __cunit_fail_file; \
    extern int __cunit_fail_line; \
    extern jmp_buf __cunit_jmp_env; \
    long __aa = (long)(a); \
    long __bb = (long)(b); \
    if (__aa != __bb) { \
        __cunit_fail_file = __FILE__; \
        __cunit_fail_line = __LINE__; \
        fprintf(stderr, "%s:%d: Expected %s == %s but got %ld vs %ld\n", \
                __FILE__, __LINE__, #a, #b, __aa, __bb); \
        longjmp(__cunit_jmp_env, 1); \
    } \
} while(0)

#define CUNIT_ASSERT_STR_EQ(a, b) do { \
    extern const char* __cunit_fail_file; \
    extern int __cunit_fail_line; \
    extern jmp_buf __cunit_jmp_env; \
    if (strcmp((a), (b)) != 0) { \
        __cunit_fail_file = __FILE__; \
        __cunit_fail_line = __LINE__; \
        fprintf(stderr, "%s:%d: Expected %s == %s but got \"%s\" vs \"%s\"\n", \
                __FILE__, __LINE__, #a, #b, (a), (b)); \
        longjmp(__cunit_jmp_env, 1); \
    } \
} while(0)

int cunit_run_all_tests(void);
int cunit_run_all_tests_verbose(FILE* output_file);

#endif
