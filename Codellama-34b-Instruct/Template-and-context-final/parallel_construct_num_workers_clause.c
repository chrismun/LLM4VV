#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_WORKERS 4

int main() {
    int err = 0;

    // Set the number of workers for the parallel construct
    acc_set_num_workers(NUM_WORKERS);

    // Create a parallel construct with the specified number of workers
    #pragma acc parallel num_workers(NUM_WORKERS)
    {
        // Do some work here
    }

    // Check for errors
    if (acc_get_num_workers() != NUM_WORKERS) {
        err = 1;
    }

    return err;
}