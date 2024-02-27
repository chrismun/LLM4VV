#include "acc_testsuite.h"
#ifndef T1
//T1:compute,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int num_elements = 1000;
    int *host_array = (int *)malloc(num_elements * sizeof(int));
    int *result_array = (int *)malloc(num_elements * sizeof(int));
    int *device_array;

    // Initialize host array with random data
    for (int i = 0; i < num_elements; ++i) {
        host_array[i] = rand() / (RAND_MAX / 100); // Random integers [0, 100)
    }

    // Allocate and copy data to device array
    #pragma acc enter data copyin(host_array[0:num_elements]) create(device_array[0:num_elements])

    // Perform a parallel operation asynchronously (in async queue 1)
    #pragma acc parallel loop async(1) copyout(device_array[0:num_elements])
    for (int i = 0; i < num_elements; ++i) {
        device_array[i] = host_array[i] + 1; // Increment each element
    }

    // Ensure that the next operation waits for the completion of the previous async operation
    #pragma acc parallel loop wait(1) copyout(result_array[0:num_elements])
    for (int i = 0; i < num_elements; ++i) {
        result_array[i] = device_array[i] + 1; // Increment each element again
    }

    #pragma acc exit data delete(device_array[0:num_elements])

    // Verify the result
    for (int i = 0; i < num_elements; ++i) {
        if (result_array[i] != host_array[i] + 2) { // Each element should be incremented twice
            err++;
        }
    }

    free(host_array);
    free(result_array);
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