#include "acc_testsuite.h"
#ifndef T1
//T1:{data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a_host = (int*)malloc(size * sizeof(int));
    int *a_device;

    // Initialize host array with random values which we'll override on the device.
    for (int i = 0; i < size; ++i) {
        a_host[i] = rand() / (RAND_MAX / 100);
    }

    // Use OpenACC data construct with create clause
    #pragma acc data create(a_device[0:size])
    {
        // Allocate memory on the device and copy host array to the device array.
        #pragma acc enter data copyin(a_host[0:size])

        // Manual initialization on the device, setting to a known value
        #pragma acc parallel loop present(a_device)
        for (int i = 0; i < size; ++i) {
            a_device[i] = 42; // Setting all elements to a constant value to check later
        }

        // Copy device array back to the host array
        #pragma acc exit data copyout(a_host[0:size])
    }

    // Verify all elements are set to 42
    for (int i = 0; i < size; ++i) {
        if (a_host[i] != 42) {
            err++;
        }
    }

    free(a_host);
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