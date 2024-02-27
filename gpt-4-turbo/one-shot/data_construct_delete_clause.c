#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h" // Assuming this header contains necessary utility macros and definitions

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t* orig_a = (real_t*)malloc(n * sizeof(real_t));
    real_t* a = (real_t*)malloc(n * sizeof(real_t));

    // Initializing data
    for (int x = 0; x < n; ++x) {
        orig_a[x] = rand() / (real_t)(RAND_MAX / 10);
        a[x] = orig_a[x]; // Copying values to a[], to work with OpenACC
    }

    // Using OpenACC data region and delete clause
    #pragma acc data copy(a[0:n])
    {
        // Performing some computation, could be dummy as the focus is on the delete clause
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                a[x] += 1; // Some operation on the data
            }
        }
        // The delete clause should remove 'a' from the device at the end of the data region
        #pragma acc exit data delete(a[0:n])
    }

    // Verifying that the data has been updated correctly, indicating it was indeed on the device and then deleted as per the clause
    for (int x = 0; x < n; ++x) {
        if (fabs((orig_a[x] + 1) - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(orig_a);
    free(a);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}