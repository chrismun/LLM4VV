#include <iostream>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int num_workers = 4; // Specify the number of worker threads

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Parallel region with num_workers threads
    #pragma acc parallel loop num_workers(num_workers)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check the results
    for (int i = 0; i < N; i++) {
        if (c[i] != i + i) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}