#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_WORKERS 4

int main() {
    int failcode = 0;

    // Initialize the OpenACC environment
    acc_init(acc_device_default);

    // Set the number of workers to 4
    acc_set_num_workers(NUM_WORKERS);

    // Create a parallel region with 4 workers
    #pragma acc parallel num_workers(NUM_WORKERS)
    {
        // Create a kernel with 4 workers
        #pragma acc kernels num_workers(NUM_WORKERS)
        {
            // Do some work
            printf("Hello from worker %d\n", acc_get_worker_id());
        }
    }

    // Check the number of workers that are active
    int num_workers = acc_get_num_workers();
    if (num_workers != NUM_WORKERS) {
        printf("Error: expected %d workers, but got %d\n", NUM_WORKERS, num_workers);
        failcode = 1;
    }

    // Clean up the OpenACC environment
    acc_shutdown(acc_device_default);

    return failcode;
}