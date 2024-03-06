#include "acc_testsuite.h"

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(sizeof(int));
    *host_data = 1;

    #pragma acc data copyin(host_data[0:1])
    {
        // Increment the structured reference counter
        #pragma acc enter data copyin(host_data[0:1])

        // Decrement the structured reference counter
        #pragma acc exit data delete(host_data[0:1])

        // Increment the dynamic reference counter
        #pragma acc enter data copyin(host_data[0:1])

        // Decrement the dynamic reference counter
        #pragma acc exit data delete(host_data[0:1])
    }

    // Check that the data is correctly deallocated
    if (*host_data != 0) {
        err++;
    }

    free(host_data);

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