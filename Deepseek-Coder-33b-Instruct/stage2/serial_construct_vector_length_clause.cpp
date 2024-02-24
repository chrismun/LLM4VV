#include <iostream>
#include <cstdlib>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int *dev_a, *dev_b, *dev_c;

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
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

    // Perform vector addition
    #pragma acc parallel loop vector_length(128)
    for (int i = 0; i < N; ++i) {
        dev_c[i] = dev_a[i] + dev_b[i];
    }

    // Copy data back to the host
    acc_memcpy_from_device(c, dev_c, N * sizeof(int));

    // Verify results
    for (int i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;

    // Free memory
    acc_free(dev_a);
    acc_free(dev_b);
    acc_free(dev_c);

    return 0;
}