#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int *dev_a, *dev_b, *dev_c;
    int i;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Allocate memory on the device
    dev_a = (int*)acc_malloc(N * sizeof(int));
    dev_b = (int*)acc_malloc(N * sizeof(int));
    dev_c = (int*)acc_malloc(N * sizeof(int));

    // Copy data to the device
    acc_memcpy_to_device(dev_a, a, N * sizeof(int));
    acc_memcpy_to_device(dev_b, b, N * sizeof(int));

    // Perform the computation
    #pragma acc kernels copyout(dev_c[0:N]) private(i)
    for (i = 0; i < N; i++) {
        dev_c[i] = dev_a[i] + dev_b[i];
    }

    // Copy data back to the host
    acc_memcpy_from_device(c, dev_c, N * sizeof(int));

    // Verify the results
    for (i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            std::cout << "Error at index " << i << ": expected " << 2 * i << ", got " << c[i] << std::endl;
            return 1;
        }
    }

    // Free the device memory
    acc_free(dev_a);
    acc_free(dev_b);
    acc_free(dev_c);

    return 0;
}