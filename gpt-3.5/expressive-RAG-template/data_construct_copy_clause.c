#include "acc_testsuite.h"
#ifndef T1
// T1: data construct copy clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int* host_data = (int*)malloc(N * sizeof(int));
    int* device_data = (int*)malloc(N * sizeof(int));

    // Initialize host_data
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Transfer data to device
    #pragma acc data copy(host_data[0:N]) copyout(device_data[0:N])
    {
        // Compute on device
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            device_data[i] = 2 * host_data[i];
        }
    }

    // Verify the result
    for (int i = 0; i < N; i++) {
        if (device_data[i] != 2 * host_data[i]) {
            err = 1;
            break;
        }
    }

    free(host_data);
    free(device_data);
    
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