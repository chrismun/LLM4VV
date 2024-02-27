#include "acc_testsuite.h"
#ifndef T1
// T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int n = 1024;
    int* host_array = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i){
        host_array[i] = rand() / (RAND_MAX / 100); // Initialize with random values between 0-99
    }

    int* device_array = (int*)acc_malloc(n * sizeof(int));
    if (device_array == NULL){
        return ++err;
    }

    acc_memcpy_to_device(device_array, host_array, n * sizeof(int));

    #pragma acc parallel loop present(device_array)
    for (int i = 0; i < n; ++i){
        device_array[i] += 1; // Simple operation to test
    }

    acc_memcpy_from_device(host_array, device_array, n * sizeof(int));

    for (int i = 0; i < n; ++i){
        if (host_array[i] != (rand() / (RAND_MAX / 100) + 1)){
            err++;
            break; // One error is sufficient to indicate a problem
        }
        srand(SEED); // Reset seed to ensure correct values are generated for comparison
    }

    acc_free(device_array);
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
        srand(SEED); // Reset the seed for each test to ensure consistency.
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}