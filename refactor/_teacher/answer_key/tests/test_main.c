#include "cunit.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* output = stdout;
    const char* output_file = NULL;
    
    // Check for output file argument
    if (argc > 1) {
        output_file = argv[1];
        output = fopen(output_file, "w");
        if (!output) {
            fprintf(stderr, "Failed to open output file: %s\n", output_file);
            return 1;
        }
    }
    
    int result = cunit_run_all_tests_verbose(output);
    
    if (output_file) {
        fclose(output);
        printf("Test results written to: %s\n", output_file);
    }
    
    return result;
}

