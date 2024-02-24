#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Parallel region with firstprivate clause
    #pragma acc parallel loop firstprivate(a)
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != i) {
            std::cout << "Test failed\n";
            return 1;
        }
    }

    std::cout << "Test passed\n";
    return 0;
}