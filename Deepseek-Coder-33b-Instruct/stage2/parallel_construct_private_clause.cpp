#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Parallel region with private copy of i
    #pragma acc parallel copy(a[0:N], b[0:N])
    {
        #pragma acc loop private(i)
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Check if the parallel region worked correctly
    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            std::cout << "Error: a[" << i << "] = " << a[i] << ", b[" << i << "] = " << b[i] << std::endl;
            return 1; // Return non-zero to indicate an error
        }
    }

    std::cout << "Success: The parallel construct private clause is working correctly." << std::endl;
    return 0; // Return zero to indicate success
}