#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

int main() {
    int num_gangs = 10;
    int num_workers = 10;
    int num_threads = 10;

    // Set the number of gangs
    acc_set_num_gangs(num_gangs);

    // Set the number of workers
    acc_set_num_workers(num_workers);

    // Set the number of threads
    acc_set_num_threads(num_threads);

    // Create a parallel region
    #pragma acc parallel
    {
        // Do some work
        std::cout << "Hello from gang " << acc_get_gang_id() << " worker " << acc_get_worker_id() << " thread " << acc_get_thread_id() << std::endl;
    }

    return 0;
}