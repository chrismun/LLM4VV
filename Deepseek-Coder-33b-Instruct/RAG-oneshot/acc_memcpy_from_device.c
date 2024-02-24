#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *d_data, *h_data;

    // Allocate memory on the device
    d_data = (int*)acc_malloc(n * sizeof(int));

    // Allocate memory on the host
    h_data = (int*)malloc(n * sizeof(int));

    // Initialize data on the device
    #pragma acc parallel loop copyin(d_data[0:n])
    for (int i = 0; i < n; i++) {
        d_data[i] = i;
    }

    // Copy data from device to host
    acc_memcpy_from_device(h_data, d_data, n * sizeof(int));

    // Print the data
    for (int i = 0; i < n; i++) {
        printf("%d ", h_data[i]);
    }
    printf("\n");

    // Free memory
    acc_free(d_data);
    free(h_data);

    return 0;
}