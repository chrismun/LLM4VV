#include <openacc.h>
#include <iostream>

#define N 1000000

int main() {
    int *a = new int[N];
    int *b = new int[N];

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Perform computation in parallel
    #pragma acc parallel loop async(1)
    for (int i = 0; i < N; i++) {
        b[i] = a[i] * 2;
    }

    // Wait for all asynchronous operations to complete
    while (acc_async_wait(1) != 0) {
        // Do some other work while waiting
        std::cout << "Waiting for async operations to complete..." << std::endl;
    }

    // Check the results
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            std::cout << "Test failed!" << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed!" << std::endl;
    return 0;
}