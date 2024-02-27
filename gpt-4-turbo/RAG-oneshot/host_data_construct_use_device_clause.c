#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1: host_data,use_device,V:3.0
int test_host_data_use_device() {
    int err = 0;
    const int n = 1024;
    float *a = (float*)malloc(n * sizeof(float));
    float *b = (float*)malloc(n * sizeof(float));

    // Initialize host data
    for (int i = 0; i < n; ++i){
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Suppose device_api_function is a device-level API accepting device pointers.
    extern void device_api_function(float *device_ptr, int size);

    // Copy data to device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Use device pointer directly in a low-level API
        #pragma acc host_data use_device(a)
        {
            device_api_function(a, n);
        }

        // Example computation (copy in this case) on the device
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            b[i] = a[i];
        }
    }

    // Verification
    for (int i = 0; i < n; ++i) {
        if (b[i] != (float)i) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = test_host_data_use_device();
    if (failed != 0){
        failcode = 1;
        printf("Test failed with %d errors.\n", failed);
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}