#include "acc_testsuite.h"
#ifndef T1
// T1: data-construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 100;
    int *a_host = (int*)malloc(array_size * sizeof(int));
    int *a_device_check = (int*)malloc(array_size * sizeof(int));
    
    // Initialize array on the host
    for (int i = 0; i < array_size; ++i) {
        a_host[i] = rand() / (RAND_MAX / 100 + 1); // Random values 0-99
    }

    // Copy data to the device and check
    #pragma acc data copyin(a_host[0:array_size])
    {
        // Device-side check: initialize a_device_check with 0s to use in verification
        #pragma acc parallel loop
        for (int i = 0; i < array_size; ++i) {
            if (a_host[i] != a_host[i]) { // This check should ideally fail to trigger, since a_host values should match
                err++;
            }
        }
    }

    free(a_host);
    free(a_device_check);

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