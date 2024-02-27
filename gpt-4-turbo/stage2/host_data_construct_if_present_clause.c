#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:host_data construct if_present clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // Using a fixed seed for reproducibility

    const int size = 1024;
    float *host_array = (float *)malloc(size * sizeof(float));
    float *device_copy;

    // Initialize host array
    for (int i = 0; i < size; i++) {
        host_array[i] = rand() / (float)RAND_MAX;
    }

    // Attempt to allocate and copy to device memory
    #pragma acc enter data copyin(host_array[0:size]) if_present

    // Use host_data with if_present
    #pragma acc host_data use_device(host_array) if_present
    {
        device_copy = acc_deviceptr(host_array);
        if (device_copy == NULL) {
            printf("Device pointer not available.\n");
            err = 1; // Should not happen, indicates malfunctioning if_present
        }
    }

    // Finalize by releasing device memory
    #pragma acc exit data delete(host_array[0:size]) if_present

    free(host_array);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}