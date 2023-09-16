#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int i;
    int *data, *dev_data;

    data = (int *)malloc(N * sizeof(int));
    dev_data = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Map data to the device
    #pragma acc enter data copyin(data[0:N])
    #pragma acc enter data create(dev_data[0:N])

    // Launch a kernel to modify the data on the device
    #pragma acc kernels present(data[0:N], dev_data[0:N])
    {
        for (i = 0; i < N; i++) {
            dev_data[i] = data[i] * 2;
        }
    }

    // Unmap the data from the device
    #pragma acc exit data delete(dev_data[0:N])

    // Check that the original data on the host remains unchanged
    for (i = 0; i < N; i++) {
        if (data[i] != i) {
            printf("Test failed: original data on host was modified.\n");
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}