#include "acc_testsuite.h"

#ifndef T2
//T2:runtime-api,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t)); // Source
    real_t * b = (real_t *)malloc(n * sizeof(real_t)); // Destination

    // Initialize source data on the host
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy SOURCE data to DEVICE
    acc_memcpy_to_device(b, a, n * sizeof(real_t));

    // Copy DATA from one DEVICE location to another
    acc_memcpy_device(b, a, n * sizeof(real_t));
    // Copy RESULT from DEVICE back to the HOST
    acc_memcpy_from_device(a, b, n * sizeof(real_t));

    // Verify data was correctly copied
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T2
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed != 0){
        failcode += (1 << 1);
    }
#endif
    return failcode;
}