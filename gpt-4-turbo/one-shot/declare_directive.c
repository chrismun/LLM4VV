#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Assuming definition of real_t, SEED, NUM_TEST_CALLS, and PRECISION
#define real_t float
#define SEED 12345
#define NUM_TEST_CALLS 10
#define PRECISION 0.001f
#define n 1000

real_t a[n], b[n]; // Global arrays

#pragma acc declare copyin(a)
#pragma acc declare copyout(b)

// Initialize 'a' array
void initialize(){
    srand(SEED);
    #pragma acc kernels
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
}

// Perform computation - copy 'a' to 'b'
void compute(){
    #pragma acc kernels
    for (int x = 0; x < n; ++x){
        b[x] = a[x];
    }
}

// Test for correct implementation
int test_declare_directive(){
    int err = 0;
    
    initialize(); // Prepare data
    compute(); // Perform computation on the data
    
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_declare_directive();
    }
    if (failed != 0){
        failcode = 1;
    }

    if (failcode) {
        printf("Test failed with %d errors.\n", failed);
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}