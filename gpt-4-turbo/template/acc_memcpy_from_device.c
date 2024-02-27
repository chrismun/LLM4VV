#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,API,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *host_array = (int *)malloc(size * sizeof(int));
    int *device_array;
    int *result_array = (int *)malloc(size * sizeof(int));

    // Initialize host array with random values
    for (int i = 0; i < size; ++i) {
        host_array[i] = rand() % 100;
    }

    // Allocate memory on the device
    device_array = (int *)acc_malloc(size * sizeof(int));
    if (device_array == NULL) {
        fprintf(stderr, "Failed to allocate memory on the device.\n");
        free(host_array);
        free(result_array);
        return 1; // Indicate error
    }

    // Copy data from host to device
    acc_memcpy_to_device(device_array, host_array, size * sizeof(int));

    // Copy data back from device to a new host array for verification
    acc_memcpy_from_device(result_array, device_array, size * sizeof(int));

    // Verify data
    for (int i = 0; i < size; ++i) {
        if (result_array[i] != host_array[i]) {
            err++;
            break; // Found an error, no need to check further
        }
    }

    // Cleanup
    free(host_array);
    free(result_array);
    acc_free(device_array);

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