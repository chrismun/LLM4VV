#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int *dev_a, *dev_b;
    int i, err = 0;

    // Initialize a and b
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Allocate memory on the device
    dev_a = (int*)acc_malloc(N * sizeof(int));
    dev_b = (int*)acc_malloc(N * sizeof(int));

    // Copy a to dev_a
    acc_memcpy_device(dev_a, a, N * sizeof(int));

    // Copy dev_a to dev_b
    acc_memcpy_device(dev_b, dev_a, N * sizeof(int));

    // Copy dev_b to b
    acc_memcpy_device(b, dev_b, N * sizeof(int));

    // Check that b is the same as a
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            err = 1;
        }
    }

    // Free memory on the device
    acc_free(dev_a);
    acc_free(dev_b);

    return err;
}