#include "acc_testsuite.h"
#ifndef T1
//T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int array_size = 1024;
    int *host_array = (int*)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; ++i) {
        host_array[i] = rand();
    }

    // Pointer for device array will be obtained via OpenACC runtime
    int *device_array;

    // Marking data for copy in
#pragma acc enter data copyin(host_array[0:array_size])
#pragma acc parallel private(device_array)
    {
#pragma acc loop
        for (int i = 0; i < array_size; ++i) {
            // Using the default device pointer obtained to access data on the device
            device_array[i] = host_array[i] * 2;
        }
    }

    // Copying data back for verification
#pragma acc exit data copyout(host_array[0:array_size])

    // Verifying the data was correctly managed and calculations were performed on the device
    for (int i = 0; i < array_size; ++i) {
        if (host_array[i] != 2 * (rand())) { // Note: This check assumes the rand() call sequence is unchanged
            err++;
        }
    }

    free(host_array);

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