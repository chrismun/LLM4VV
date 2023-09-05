++
#include <stdio.h>
#include <openacc.h>

#define N 10

int main() {
    int data[N];
    int *data_device;

    // Allocate device memory using acc_create
    data_device = (int *)acc_create(data, N * sizeof(int));

    // Copy data to device memory using acc_copyin
    acc_copyin(data, N * sizeof(int));

    // Print the data on the device
    #pragma acc parallel loop present(data_device)
    for (int i = 0; i < N; i++) {
        printf("Data on device: %d\n", data_device[i]);
    }

    // Free the device memory
    acc_delete(data_device);

    return 0;
}