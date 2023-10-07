#include "acc_testsuite.h"
#ifndef T1
//T1:acc copyin,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize host data
    int *host_data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        host_data[i] = rand() % 100;
    }

    // Copy host data to device using acc_enter_data
    int *device_data = NULL;
    #pragma acc enter data copyin(host_data[0:N])
    device_data = (int *)acc_deviceptr(host_data);

    // Perform some computation on the device
    #pragma acc parallel loop present(device_data[0:N])
    for (int i = 0; i < N; i++) {
        device_data[i] = device_data[i] * 2;
    }

    // Copy device data back to host using acc_exit_data
    #pragma acc exit data copyout(host_data[0:N])

    // Verify the computation
    for (int i = 0; i < N; i++) {
        if (host_data[i] != 2 * (i+1)) {
            err = 1;
            break;
        }
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
        failcode += (1 << 0);
    }
#endif
    return failcode;
}