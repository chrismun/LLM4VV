#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// Assuming the existence of a specific test suite header for OpenACC
// #include "acc_testsuite.h"

#ifndef TEST_WAIT_DIRECTIVE
// This test checks for the proper implementation of the wait directive.
int test_wait_directive(){
    const int n = 1024;
    int errors = 0;
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    
    // Initializing data
    for (int i = 0; i < n; ++i){
        a[i] = i * 1.0f;
        b[i] = -1.0f;
    }

    // Perform operations asynchronously
    #pragma acc parallel loop copyin(a[0:n]) copyout(b[0:n]) async(1)
    for (int i = 0; i < n; ++i){
        b[i] = a[i] * 2.0f;
    }

    // Wait for the completion of all operations in the async queue 1
    #pragma acc wait(1)

    // Validation
    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - a[i] * 2.0f) > 0.00001f){
            errors += 1;
        }
    }

    free(a);
    free(b);

    return errors;
}
#endif

int main() {
    int failed = test_wait_directive();
    
    printf("Test %s\n", failed ? "FAILED" : "PASSED");

    return failed ? 1 : 0;
}