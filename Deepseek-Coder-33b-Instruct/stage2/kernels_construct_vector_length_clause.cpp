#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Perform vector addition
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N]) vector_length(128)
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verify results
    for (int i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}