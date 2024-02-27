#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *host_array = (float*)malloc(size * sizeof(float));
    float *device_array = (float*)acc_malloc(size * sizeof(float));

    // Ensure memory was allocated
    if (host_array == NULL || device_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Initialize device memory
    #pragma acc parallel loop copyout(device_array[0:size])
    for (int i = 0; i < size; ++i) {
        device_array[i] = rand() / (float)RAND_MAX;
    }

    // Retrieve data from device and check if the operation was successful
    acc_copyout(device_array, size * sizeof(float));

    // Copy data back to host to verify
    #pragma acc update host(host_array[0:size])
    for (int i = 0; i < size; ++i) {
        if (host_array[i] != device_array[i]) {
            err++;
        }
    }

    // Cleanup
    free(host_array);
    acc_free(device_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif
    if(failcode == 0){
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    return failcode;
}