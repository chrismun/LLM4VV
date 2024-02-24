#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region
    int *data = (int*)malloc(sizeof(int));
    *data = 0;

    // Increment the reference counter
    #pragma acc data copyin(data[0:1])
    {
        // Increment the value in the data region
        #pragma acc atomic update
        data[0]++;
    }

    // Check that the reference counter was incremented
    if (data[0] != 1) {
        err++;
    }

    // Decrement the reference counter
    #pragma acc data copyin(data[0:1])
    {
        // Decrement the value in the data region
        #pragma acc atomic update
        data[0]--;
    }

    // Check that the reference counter was decremented
    if (data[0] != 0) {
        err++;
    }

    free(data);

    return err;
}
#endif

int main(){
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