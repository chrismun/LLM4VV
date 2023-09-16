++
#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int a[SIZE];

    // Initiate array data
    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand();
    }

    #pragma acc declare device_resident(a)

    #pragma acc parallel loop
    for(int i = 0; i < SIZE; ++i) {
        a[i] = a[i] + 1;
    }

    #pragma acc update host(a)

    // Check array data
    for (int i = 0; i < SIZE; ++i) {
        if (a[i] != a[i] + 1) {
            err = 1;
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}