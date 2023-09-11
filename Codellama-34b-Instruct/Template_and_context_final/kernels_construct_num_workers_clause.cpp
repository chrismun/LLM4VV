#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_WORKERS 4

int main() {
    int err = 0;
    srand(SEED);

    // Create a kernel with 4 workers
    #pragma acc kernels num_workers(NUM_WORKERS)
    {
        // Do some work here
    }

    // Check if the kernel was executed correctly
    if (err != 0) {
        std::cerr << "Error: Kernel execution failed" << std::endl;
        return 1;
    }

    return 0;
}