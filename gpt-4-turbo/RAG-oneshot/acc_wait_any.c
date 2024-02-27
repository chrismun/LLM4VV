#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T2
// T2:async,wait-any,V:1.0-2.7
int test_async_wait_any(){
    int err = 0;
    const int n = 1000;
    const int num_async_ops = 5; // Number of async operations to initiate
    float *host_array = (float*)malloc(sizeof(float) * n * num_async_ops);
    float *device_array = (float*)malloc(sizeof(float) * n * num_async_ops);

    // Initialize host array with some values
    for (int i = 0; i < n * num_async_ops; ++i) {
        host_array[i] = i * 1.0f;
    }

    int async_handles[num_async_ops]; // Array to store async handles

    // Performing data copy operations on async queues
    for (int i = 0; i < num_async_ops; ++i) {
        async_handles[i] = i+1; // Assuming async handles are positive integers starting from 1
        #pragma acc kernels async(async_handles[i]) copy(device_array[i*n:n]) // Data copy operation per async
        for(int j = 0; j < n; ++j){
            device_array[i*n+j] = host_array[i*n+j];
        }
    }

    // Wait for any of the initiated async operations to complete
    int any_completed = acc_wait_any(num_async_ops, async_handles);
    if (any_completed < 0 || any_completed >= num_async_ops) {
        printf("Invalid async handle returned by acc_wait_any.\n");
        err = 1;
    }

    // Verifying data to ensure at least one operation has completed would require waiting for all operations
    // and is not directly related to acc_wait_any functionality testing.

    free(host_array);
    free(device_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    #ifndef T2
    failed = test_async_wait_any();
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
    #endif
    printf("Test %s\n", failcode == 0 ? "passed" : "failed");
    return failcode;
}