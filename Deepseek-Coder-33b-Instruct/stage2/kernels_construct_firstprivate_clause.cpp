#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int *dev_a, *dev_b, *dev_c;

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Allocate memory on device
    dev_a = (int*)acc_malloc(N * sizeof(int));
    dev_b = (int*)acc_malloc(N * sizeof(int));
    dev_c = (int*)acc_malloc(N * sizeof(int));

    // Copy data to device
    acc_memcpy_to_device(dev_a, a, N * sizeof(int));
    acc_memcpy_to_device(dev_b, b, N * sizeof(int));

    // Execute kernel
    #pragma acc kernels copyout(dev_c) firstprivate(dev_a, dev_b)
    for (int i = 0; i < N; i++) {
        dev_c[i] = dev_a[i] + dev_b[i];
    }

    // Copy data back to host
    acc_memcpy_from_device(c, dev_c, N * sizeof(int));

    // Verify results
    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}