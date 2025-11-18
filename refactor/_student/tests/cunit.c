#include "cunit.h"
#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <setjmp.h>
#include <sys/resource.h>
#ifdef __linux__
#include <sys/prctl.h>
#endif
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
        // Disable core dump before jumping (in case it wasn't set earlier)
        #ifndef _WIN32
        struct rlimit rl;
        rl.rlim_cur = 0;
        rl.rlim_max = 0;
        setrlimit(RLIMIT_CORE, &rl);
        #ifdef __linux__
        prctl(PR_SET_DUMPABLE, 0, 0, 0, 0);
        #endif
        #endif
        // Jump back to test runner - this prevents default signal behavior
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
    
    // Disable core dumps to prevent "core dumped" messages
    #ifndef _WIN32
    struct rlimit rl;
    rl.rlim_cur = 0;
    rl.rlim_max = 0;
    setrlimit(RLIMIT_CORE, &rl);
    #ifdef __linux__
    prctl(PR_SET_DUMPABLE, 0, 0, 0, 0);
    #endif
    #endif
    
    // Install signal handler for SIGSEGV (Unix/Linux/WSL)
    #ifndef _WIN32
    struct sigaction sa;
    sa.sa_handler = segfault_handler;
    sigemptyset(&sa.sa_mask);
    // SA_NODEFER allows handler to be called recursively if needed
    // SA_ONSTACK is not needed but SA_RESTART might help
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL);
    
    // Ensure SIGSEGV is not blocked
    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGSEGV);
    sigprocmask(SIG_UNBLOCK, &block_set, NULL);
    #else
    // On Windows/WSL, signal handling should work
    signal(SIGSEGV, segfault_handler);
    #endif
    
    for (int i = 0; i < __cunit_test_count; ++i) {
        fprintf(output_file, "[RUN] %s", __cunit_tests[i].name);
        fprintf(stderr, "[RUN] %s", __cunit_tests[i].name);
        fflush(output_file);
        fflush(stderr);
        
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
                fprintf(stderr, " ... [PASS]\n");
                fflush(output_file);
                fflush(stderr);
                passed++;
            } else {
                __cunit_in_test = 0;
                fprintf(output_file, " ... [FAIL]\n");
                fprintf(output_file, "| `%s` | ❌ FAIL |\n", __cunit_tests[i].name);
                fprintf(stderr, " ... [FAIL]\n");
                if (__cunit_fail_file) {
                    fprintf(stderr, "  %s:%d: %s\n", __cunit_fail_file, __cunit_fail_line, 
                            __cunit_fail_msg ? __cunit_fail_msg : "Test failed");
                    fprintf(output_file, "  - **Error**: %s:%d: %s\n", __cunit_fail_file, __cunit_fail_line,
                            __cunit_fail_msg ? __cunit_fail_msg : "Test failed");
                }
                fflush(output_file);
                fflush(stderr);
                failed++;
            }
        } else {
            // Segfault occurred - siglongjmp returned here
            __cunit_in_test = 0;
            fprintf(output_file, " ... [CRASH]\n");
            fprintf(output_file, "| `%s` | 💥 CRASH (Segfault) |\n", __cunit_tests[i].name);
            fprintf(stderr, " ... [CRASH]\n");
            fprintf(stderr, "  SEGFAULT in test: %s\n", __cunit_tests[i].name);
            fprintf(output_file, "  - **Error**: SEGFAULT - Function crashed (likely NULL pointer dereference)\n");
            fflush(output_file);
            fflush(stderr);
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
    
    // Print prominent summary to stdout/stderr
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("TEST SUMMARY\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Total Tests:  %d\n", __cunit_test_count);
    printf("Passed:       %d ✅\n", passed);
    printf("Failed:       %d ❌\n", failed);
    if (crashed > 0) {
        printf("Crashed:      %d 💥\n", crashed);
    }
    printf("Success Rate: %.1f%%\n", 
           __cunit_test_count > 0 ? (100.0 * passed / __cunit_test_count) : 0.0);
    printf("═══════════════════════════════════════════════════════════\n");
    printf("\n");
    
    return (failed == 0) ? 0 : 1;
}

