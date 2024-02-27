#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Include OpenACC support

#ifndef N
#define N 100
#endif

// Define a simple macro to check errors
#define checkErr(err) if(err != 0){ printf("Error occurred: %d\n", err); exit(1); }

int test_acc_on_device() {
    int err = 0;
    int *a = (int *)malloc(N * sizeof(int));
    int deviceExecution = 0; // Flag to check execution on device

    // Initialize array
    for (int x = 0; x < N; ++x){
        a[x] = x;
    }

    // OpenACC region to offload to the device if available
    #pragma acc parallel copy(a[0:N])
    {
        // Check if this region is executing on the device
        if (acc_on_device(acc_device_any)) {
            deviceExecution = 1;
        }

        // Simple operation to ensure the compiler does not optimize out the loop
        #pragma acc loop
        for (int x = 0; x < N; ++x){
            a[x] = a[x] + 1;
        }
    }

    // Verify results and whether execution happened on a device
    for (int x = 0; x < N; ++x){
        if (a[x] != x + 1){
            err++;
        }
    }

    if (!deviceExecution) {
        printf("Code did not execute on an accelerator device.\n");
    } else {
        printf("Code executed on an accelerator device.\n");
    }

    free(a);
    return err;
}

int main() {
    int failcode = 0;
    int failed = test_acc_on_device();

    if (failed != 0) {
        printf("Test failed with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}