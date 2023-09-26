#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
int test1() {
    int err = 0;
    srand(SEED);

    float *test;
    float *compare;

    test = (float *)malloc(10 * sizeof(float));
    compare = (float *)malloc(10 * sizeof(float));

    #pragma acc parallel loop async(1)
    for (int i = 0; i < 10; i++) {
        test[i] = i + 1;
    }

    // wait directive to synchronize - wait till async(1) is completed.
    #pragma acc wait(1)
  
    // Now copy data back to the CPU for comparison
    #pragma acc update host(test[0:10])

    for (int i = 0; i < 10; i++) {
        compare[i] = i + 1;
        if (test[i] != compare[i]) {
            err = 1;
        }
    }

    free(test);
    free(compare);

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