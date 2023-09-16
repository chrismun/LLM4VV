#include "acc_testsuite.h"
#include <math.h>

#define SEED 12345
#define PRECISION 1e-5
#define NUM_TEST_CALLS 100

// Test to verify correctness of copyin directive
int test1(){
    int err = 0;  // Error count
    srand(SEED);  // Seed the random number generator
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array a with random numbers and reset b
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy array a to the device, process it there and copy the result into array b on the host
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check results
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;  // Count errors
        }
    }

    // Cleanup
    free(a);
    free(b);

    return err;  // Return error count
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times to get more confidence in the result
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();  // Count all errors over all tests
        if (failed != 0){
            printf("Test %d failed with %d errors\n", x, failed);
            failcode = 1;  // Indicate test suite failed
        }
        else{
            printf("Test %d passed\n", x);
        }
    }
    
    // Summarize final result
    if (failcode == 0){
        printf("All tests passed\n");
    }
    else{
        printf("Some tests failed\n");
    }

    return failcode;  // Return fail code which can be evaluated by a testsuite
}