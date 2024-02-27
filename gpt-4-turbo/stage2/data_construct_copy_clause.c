#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 5

#ifndef T1
// T1:data construct copy clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int original_value = rand() % 100;  // Generate a random value to test with
    int copied_value = original_value; // This variable will be copied into and out of the ACC region

    // Data region where copied_value is both copied in and copied out
    #pragma acc data copy(copied_value)
    {
        #pragma acc parallel
        {
            // In the parallel region, just increment the copied_value to simulate computation
            copied_value += 1;
        }
    }

    // After ACC region, copied_value should be original_value + 1 due to the computation in the ACC region
    if (copied_value != original_value + 1) {
        err = 1; // If not, set an error
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("Test PASSED.\n");
    } else {
        printf("Test FAILED.\n");
    }
    return failcode;
}