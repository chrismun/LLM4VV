#include "acc_testsuite.h"

#ifndef T1
// T1:compute construct async clause,V:2.7-3.3
int test1() {
    int err = 0;
    int host_vec[N];
    int device_vec[N];

    // Generate random numbers on host
    for (int i = 0; i < N; i++) {
        host_vec[i] = rand() % 100;
    }

    // Allocate and copy data to device
    #pragma acc data copyin(host_vec[0:N]) copyout(device_vec[0:N])
    {

        // Compute on device asynchronously
        #pragma acc kernels async
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                device_vec[i] = host_vec[i] * 2;
            }
        }

        // Wait for the computation to complete
        #pragma acc wait
    }

    // Verify the computation results
    for (int i = 0; i < N; i++) {
        if (device_vec[i] != host_vec[i]*2) {
            err = 1;
            break;
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