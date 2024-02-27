#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Utility function to check if the array is correctly updated.
bool verify_result(int *data, int n, int inc_val) {
    for (int i = 0; i < n; ++i) {
        if (data[i] != i + inc_val) {
            return false;
        }
    }
    return true;
}

// Test for OpenACC serial construct
int test_serial_construct(){
    int err = 0;
    const int n = 1000;
    int *a = (int *)malloc(sizeof(int)*n);
    
    // Initialize array
    for(int i = 0; i < n; ++i){
        a[i] = i;
    }

    int inc_val = rand() % 100; // Random increment value

    // Serial construct to increment array elements
    #pragma acc serial
    for(int i = 0; i < n; ++i){
        a[i] += inc_val;
    }

    // Verify the result
    if (!verify_result(a, n, inc_val)) {
        err += 1;
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0; 
    srand(SEED);

    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_serial_construct();
    }
    if (failed != 0){
        failcode = 1;
    }

    printf("Test %s\n", (failcode == 0) ? "PASSED" : "FAILED");
    return failcode;
}