#include <openacc.h>

int main() {
    int *a, *b;
    int n = 100;

    // Allocate memory for a and b on the device
    acc_malloc(&a, n * sizeof(int));
    acc_malloc(&b, n * sizeof(int));

    // Initialize a and b on the device
    acc_init(&a, n, 0);
    acc_init(&b, n, 0);

    // Copy data from local memory to device memory
    acc_copyin(a, n, 0);
    acc_copyin(b, n, 0);

    // Perform computation on device
    acc_parallel(a, b, n);

    // Copy data from device memory to local memory
    acc_copyout(a, n, 0);
    acc_copyout(b, n, 0);

    // Free memory on device
    acc_free(a);
    acc_free(b);

    return 0;
}