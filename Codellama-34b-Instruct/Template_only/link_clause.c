#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    cudaMalloc((void**)&dev_array, 100 * sizeof(int));

    // Create a host array
    int *host_array = (int*)malloc(100 * sizeof(int));

    // Initialize the host array with random values
    for (int i = 0; i < 100; i++) {
        host_array[i] = rand();
    }

    // Copy the host array to the device array
    cudaMemcpy(dev_array, host_array, 100 * sizeof(int), cudaMemcpyHostToDevice);

    // Create a link clause
    acc_link_clause link_clause;
    link_clause.type = ACC_LINK_CLAUSE_DEVICE;
    link_clause.device = dev_array;
    link_clause.host = host_array;
    link_clause.size = 100 * sizeof(int);

    // Validate the link clause
    if (acc_validate_link_clause(link_clause) != ACC_SUCCESS) {
        err = 1;
    }

    // Free the device and host arrays
    cudaFree(dev_array);
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