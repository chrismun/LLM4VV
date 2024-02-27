#include "acc_testsuite.h"
#ifndef T1
// T1:parallel,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size], b[size], c[size], result[size];
    
    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = rand() / (RAND_MAX / 100);
        c[i] = 0;
    }
    
    // Offload computation to the device
    #pragma acc parallel loop copyin(a[0:size], b[0:size]) copyout(c[0:size])
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
    
    // Validate results
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
        if (c[i] != result[i]) {
            err += 1;
        }
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

    return failcode;
}