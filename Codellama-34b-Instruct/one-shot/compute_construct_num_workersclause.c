#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_WORKERS 4

int main() {
    int num_workers = 0;
    int num_devices = acc_get_num_devices(acc_device_default);

    // Set the number of workers to use for the parallel region
    acc_set_num_workers(NUM_WORKERS);

    // Launch a parallel region with the specified number of workers
    #pragma acc parallel num_workers(NUM_WORKERS)
    {
        // Get the number of workers used for the parallel region
        num_workers = acc_get_num_workers();
    }

    // Check that the correct number of workers were used
    if (num_workers != NUM_WORKERS) {
        printf("Error: Incorrect number of workers used for parallel region. Expected %d, got %d.\n", NUM_WORKERS, num_workers);
        return 1;
    }

    return 0;
}