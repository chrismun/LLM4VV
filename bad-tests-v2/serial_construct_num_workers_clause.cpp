#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_WORKERS 4

int main() {
    int err = 0;
    srand(SEED);

    // Create a serial construct with 4 workers
    #pragma acc serial num_workers(NUM_WORKERS)
    {
        // Do some work here
        std::cout << "Hello from worker " << acc_get_worker_id() << std::endl;
    }

    return err;
}