#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_WORKERS 4
#define NUM_TEST_CALLS 10

int main() {
    int failcode = 0;
    int failed;

    // Initialize the OpenACC runtime
    acc_init(acc_device_default);

    // Set the number of workers to 4
    acc_set_num_workers(NUM_WORKERS);

    // Allocate memory for the input and output arrays
    int *a = (int *)malloc(NUM_WORKERS * sizeof(int));
    int *b = (int *)malloc(NUM_WORKERS * sizeof(int));

    // Initialize the input array with random values
    for (int i = 0; i < NUM_WORKERS; i++) {
        a[i] = rand() % 100;
    }

    // Set the output array to 0
    for (int i = 0; i < NUM_WORKERS; i++) {
        b[i] = 0;
    }

    // Create a parallel region with 4 workers
    #pragma acc parallel num_workers(NUM_WORKERS)
    {
        // Create a loop with 10 iterations
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // Perform a reduction on the input array
            #pragma acc reduction(+:a[i])
            {
                // Perform a computation on the input array
                a[i] = a[i] + 1;
            }
        }
    }

    // Check the output array
    for (int i = 0; i < NUM_WORKERS; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            failcode = 1;
        }
    }

    // Free memory
    free(a);
    free(b);

    // Finalize the OpenACC runtime
    acc_finalize();

    return failcode;
}