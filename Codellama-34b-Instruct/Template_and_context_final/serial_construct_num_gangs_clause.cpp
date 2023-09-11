#include <iostream>
#include <cstdlib>

int main() {
    int num_gangs = 4; // The number of parallel gangs to use
    int num_workers = 2; // The number of workers to use

    // Create a serial construct with the specified number of gangs
    #pragma acc serial num_gangs(num_gangs)
    {
        // Do some work here
        std::cout << "Hello from gang " << acc_get_gang_id() << std::endl;
    }

    // Create a serial construct with the specified number of workers
    #pragma acc serial num_workers(num_workers)
    {
        // Do some work here
        std::cout << "Hello from worker " << acc_get_worker_id() << std::endl;
    }

    return 0;
}