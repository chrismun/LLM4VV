#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 1

int test1() {
    int err = 0;
    srand(SEED);

    const int size = 10;
    int* a_host = (int*)malloc(size * sizeof(int));
    int* a_device;

    // Initialize data
    for (int i = 0; i < size; ++i) {
        a_host[i] = rand() % 100;
    }

    // Allocate and copy data to device memory
    #pragma acc enter data copyin(a_host[0:size])
    a_device = acc_deviceptr(a_host);

    // Modify data on device for a simple test
    #pragma acc parallel loop deviceptr(a_device)
    for (int i = 0; i < size; ++i) {
        a_device[i] += 1;
    }

    // Use exit data with detach clause to detach the data
    #pragma acc exit data copyout(a_host[0:size]) detach(a_host) 

    // Attempt to access detached data
    int sum = 0;
    for (int i = 0; i < size; ++i) {
      sum += a_host[i];
    }

    // If the 'a_host' data is properly detached and copied out, 'sum' should reflect the incremented values.
    int expected_sum = 0;
    for (int i = 0; i < size; ++i) {
        expected_sum += a_host[i] + 1; // Since we incremented each element by 1 on the device
    }

    if (sum != expected_sum) {
        err = 1; // Error if the detached data does not match expected outcome
    }

    free(a_host); // Clean up host memory
    return err;
}

int main() {
    int failcode = 0;

    int failed = test1();
    if (failed != 0) {
        failcode = 1;
    }

    return failcode;
}