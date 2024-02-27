#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: data, data-region, V:1.0-2.7
int test_acc_delete(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            a[x] = a[x] + 1; // Modifying the data
        }

        // Assuming acc_delete is correctly implemented by the compiler.
        acc_delete(a, n * sizeof(real_t));
    }

    // After releasing memory using acc_delete, a should no longer affect b
    for (int x = 0; x < n; ++x){
        // Checking if 'a' was successfully deleted without affecting 'b'
        if (fabs(a[x] - (b[x] + 1)) < PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_delete();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    if (failcode) {
        printf("Test failed.\n");
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}