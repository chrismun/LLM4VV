#include <stdio.h>
#include <openacc.h>
#include <math.h>

// Define constants for test
#define N 1024
#define DEV_NUM 0 // Assuming device 0 for simplicity

// Prototype of test function
int async_operation_test(void);

int main(void) {
    int failure_code = 0;

    // Run the asynchronous operation test
    if (async_operation_test() != 0) {
        failure_code = 1; // Mark test as failed
    }

    return failure_code;
}

int async_operation_test(void) {
    int err = 0;
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Perform async operations
    int async_queue = 1; // Arbitrary async queue number

    #pragma acc data copyin(a[0:N]) copyout(b[0:N]) async(async_queue)
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            b[i] = a[i] + 1;
        }
    }

    // Check for completion using acc_async_test API
    while (!acc_async_test(async_queue)) {
        // Loop until async operation on the queue has completed
    }

    // Additional check for device specific and all queues
    if (!acc_async_test_all()) {
        printf("Error: Not all async operations completed.\n");
        err++;
    }

    if (!acc_async_test_device(async_queue, DEV_NUM)) {
        printf("Error: Device specific async operation not completed.\n");
        err++;
    }

    if (!acc_async_test_all_device(DEV_NUM)) {
        printf("Error: Not all device specific async operations completed.\n");
        err++;
    }

    // Validate the operation
    for (int i = 0; i < N; i++) {
        if (fabsf(b[i] - (a[i] + 1)) > 1e-5) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}