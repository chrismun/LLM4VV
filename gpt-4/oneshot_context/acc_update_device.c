#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

int main() {
    const int N = 100;
    float *data = malloc(N * sizeof(float));

    // Initialize data in host memory
    for (int i = 0; i < N; ++i) {
        data[i] = i;
    }

    // Now copy the data to the device asynchronously
    #pragma acc enter data copyin(data[0:N]) async

    // Update the device memory
    acc_update_device_async(data, N*sizeof(float), 0);

    // Force all previous asynchronous task to complete
    #pragma acc wait

    // Now let's modify data on host memory
    for (int i = 0; i < N; ++i) {
        data[i] = i + 1;
    }

    // Update the device data again with new values
    acc_update_device(data, N * sizeof(float));

    // Now let's change data back to original values on device
    #pragma acc parallel loop present(data)
    for (int i = 0; i < N; ++i) {
        data[i] = i;
    }

    // Update host memory from device memory
    acc_update_self(data, N * sizeof(float));

    // Now print the data and validate it
    for (int i = 0; i < N; ++i) {
        printf("data[%d] = %f\n", i, data[i]);
        if (data[i] != i) {
            printf("Data validation failed at index %d!\n", i);
            break;
        }
    }

    free(data);
    return 0;
}