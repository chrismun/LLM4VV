#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Initialize data on the host
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Allocate memory on the device
    device_data = (int*)acc_malloc(N * sizeof(int));

    // Copy data to the device
    #pragma acc data copyin(data[0:N]) copyout(device_data[0:N])
    {
        // Copy data from the host to the device
        #pragma acc update device(data[0:N])

        // Copy data from the device to the host
        #pragma acc update self(device_data[0:N])
    }

    // Check that the data was copied correctly
    for (int i = 0; i < N; i++) {
        if (data[i] != device_data[i]) {
            printf("Error: data[%d] = %d, device_data[%d] = %d\n", i, data[i], i, device_data[i]);
            return 1;
        }
    }

    printf("Data copied correctly\n");

    return 0;
}