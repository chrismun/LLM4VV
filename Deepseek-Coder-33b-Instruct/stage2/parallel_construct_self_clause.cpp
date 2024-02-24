#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Parallel region
    #pragma acc parallel loop self
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Test failed\n";
            return 1;
        }
    }

    std::cout << "Test passed\n";
    return 0;
}