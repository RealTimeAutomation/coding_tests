#include "cunit.h"
#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <setjmp.h>
#endif

jmp_buf __cunit_jmp_env;
const char* __cunit_fail_msg = NULL;
const char* __cunit_fail_file = NULL;
int __cunit_fail_line = 0;

test_case_t* __cunit_tests = NULL;
int __cunit_test_count = 0;
int __cunit_test_capacity = 0;

#ifndef _WIN32
static sigjmp_buf __cunit_sig_env;
static volatile int __cunit_in_test = 0;

static void segfault_handler(int sig) {
    (void)sig;
    if (__cunit_in_test) {
        siglongjmp(__cunit_sig_env, 1);
    } else {
        // Not in a test, let it crash normally
        signal(SIGSEGV, SIG_DFL);
        raise(SIGSEGV);
    }
}
#else
static jmp_buf __cunit_sig_env;
static volatile int __cunit_in_test = 0;

static void segfault_handler(int sig) {
    (void)sig;
    if (__cunit_in_test) {
        longjmp(__cunit_sig_env, 1);
    } else {
        signal(SIGSEGV, SIG_DFL);
        raise(SIGSEGV);
    }
}
#endif

int cunit_run_all_tests(void) {
    return cunit_run_all_tests_verbose(stdout);
}

int cunit_run_all_tests_verbose(FILE* output_file) {
    int passed = 0;
    int failed = 0;
    int crashed = 0;
    
    fprintf(output_file, "# Test Results\n\n");
    fprintf(output_file, "Running %d tests...\n\n", __cunit_test_count);
    fprintf(output_file, "| Test Name | Status |\n");
    fprintf(output_file, "|-----------|--------|\n");
    
    // Install signal handler for SIGSEGV (Unix/Linux/WSL)
    #ifndef _WIN32
    struct sigaction sa;
    sa.sa_handler = segfault_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);
    #else
    // On Windows/WSL, signal handling should work
    signal(SIGSEGV, segfault_handler);
    #endif
    
    for (int i = 0; i < __cunit_test_count; ++i) {
        fprintf(output_file, "[RUN] %s", __cunit_tests[i].name);
        fflush(output_file);
        
        __cunit_fail_msg = NULL;
        __cunit_fail_file = NULL;
        __cunit_fail_line = 0;
        __cunit_in_test = 1;
        
        #ifndef _WIN32
        if (sigsetjmp(__cunit_sig_env, 1) == 0) {
        #else
        if (setjmp(__cunit_sig_env) == 0) {
        #endif
            if (setjmp(__cunit_jmp_env) == 0) {
                __cunit_tests[i].func();
                __cunit_in_test = 0;
                fprintf(output_file, " ... [PASS]\n");
                fprintf(output_file, "| `%s` | ✅ PASS |\n", __cunit_tests[i].name);
                passed++;
            } else {
                __cunit_in_test = 0;
                fprintf(output_file, " ... [FAIL]\n");
                fprintf(output_file, "| `%s` | ❌ FAIL |\n", __cunit_tests[i].name);
                if (__cunit_fail_file) {
                    fprintf(stderr, "  %s:%d: %s\n", __cunit_fail_file, __cunit_fail_line, 
                            __cunit_fail_msg ? __cunit_fail_msg : "Test failed");
                    fprintf(output_file, "  - **Error**: %s:%d: %s\n", __cunit_fail_file, __cunit_fail_line,
                            __cunit_fail_msg ? __cunit_fail_msg : "Test failed");
                }
                failed++;
            }
        } else {
            // Segfault occurred
            __cunit_in_test = 0;
            fprintf(output_file, " ... [CRASH]\n");
            fprintf(output_file, "| `%s` | 💥 CRASH (Segfault) |\n", __cunit_tests[i].name);
            fprintf(stderr, "  SEGFAULT in test: %s\n", __cunit_tests[i].name);
            fprintf(output_file, "  - **Error**: SEGFAULT - Function crashed (likely NULL pointer dereference)\n");
            crashed++;
            failed++;
        }
    }
    
    fprintf(output_file, "\n## Summary\n\n");
    fprintf(output_file, "- **Total**: %d tests\n", __cunit_test_count);
    fprintf(output_file, "- **Passed**: %d ✅\n", passed);
    fprintf(output_file, "- **Failed**: %d ❌\n", failed);
    if (crashed > 0) {
        fprintf(output_file, "- **Crashed**: %d 💥\n", crashed);
    }
    fprintf(output_file, "- **Success Rate**: %.1f%%\n\n", 
            __cunit_test_count > 0 ? (100.0 * passed / __cunit_test_count) : 0.0);
    
    printf("\n%d/%d tests passed", passed, __cunit_test_count);
    if (crashed > 0) {
        printf(", %d crashed", crashed);
    }
    printf("\n");
    
    return (failed == 0) ? 0 : 1;
}

