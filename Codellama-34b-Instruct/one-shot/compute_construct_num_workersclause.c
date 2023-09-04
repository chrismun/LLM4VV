#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_WORKERS 4

int main() {
    int i, j, k;
    int num_workers;
    int *a, *b;

    // Allocate memory for arrays
    a = (int *)malloc(NUM_WORKERS * sizeof(int));
    b = (int *)malloc(NUM_WORKERS * sizeof(int));

    // Initialize arrays
    for (i = 0; i < NUM_WORKERS; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Use the num_workers clause to specify the number of workers to use
    #pragma acc parallel num_workers(NUM_WORKERS)
    {
        // Compute the sum of the elements in array a
        #pragma acc loop
        for (i = 0; i < NUM_WORKERS; i++) {
            b[i] = a[i] + b[i];
        }
    }

    // Check that the correct number of workers were used
    num_workers = acc_get_num_workers();
    if (num_workers != NUM_WORKERS) {
        printf("Error: Incorrect number of workers used (expected %d, got %d)\n", NUM_WORKERS, num_workers);
        return 1;
    }

    // Check that the computation was performed correctly
    for (i = 0; i < NUM_WORKERS; i++) {
        if (b[i] != a[i] + b[i]) {
            printf("Error: Incorrect result (expected %d, got %d)\n", a[i] + b[i], b[i]);
            return 1;
        }
    }

    // Free memory
    free(a);
    free(b);

    return 0;
}