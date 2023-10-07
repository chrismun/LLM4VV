#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare and initialize variables
    int n = 100;
    int *data = (int*)malloc(n * sizeof(int));
    int *devData;

    // Allocate memory on the device
    #pragma acc enter data create(data[0:n])

    // Initialize data on the device
    #pragma acc parallel loop present(data[0:n])
    for (int i = 0; i < n; i++){
        data[i] = rand();
    }

    // Allocate memory on the host
    devData = (int*)malloc(n * sizeof(int));

    // Copy data from the device to the host using acc_memcpy_from_device
    #pragma acc host_data use_device(data)
    {
        #pragma acc memcpy from(device:data[0:n]) to(host:devData[0:n])
    }

    // Verify the data on the host matches the data on the device
    for (int i = 0; i < n; i++){
        if (devData[i] != data[i]){
            err = 1;
            break;
        }
    }

    // Free memory on the device and host
    #pragma acc exit data delete(data[0:n])
    free(data);
    free(devData);

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