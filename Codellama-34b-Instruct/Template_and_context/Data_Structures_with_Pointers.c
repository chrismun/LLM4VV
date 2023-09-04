#include <openacc.h>

int main() {
    int *a, *b, *c;
    int n = 100;

    // Allocate memory for a, b, and c on the device
    acc_malloc(&a, n * sizeof(int));
    acc_malloc(&b, n * sizeof(int));
    acc_malloc(&c, n * sizeof(int));

    // Copy data from host to device
    acc_copyin(a, n * sizeof(int));
    acc_copyin(b, n * sizeof(int));
    acc_copyin(c, n * sizeof(int));

    // Perform computation on device
    acc_parallel(a, b, c, n);

    // Copy data from device to host
    acc_copyout(a, n * sizeof(int));
    acc_copyout(b, n * sizeof(int));
    acc_copyout(c, n * sizeof(int));

    // Free memory on device
    acc_free(a);
    acc_free(b);
    acc_free(c);

    return 0;
}