#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_GANGS 4
#define NUM_WORKERS 8

int main() {
    int i, j, k;
    int num_gangs, num_workers;
    int *a, *b;

    // Allocate memory for arrays
    a = (int *)malloc(NUM_GANGS * NUM_WORKERS * sizeof(int));
    b = (int *)malloc(NUM_GANGS * NUM_WORKERS * sizeof(int));

    // Initialize arrays
    for (i = 0; i < NUM_GANGS; i++) {
        for (j = 0; j < NUM_WORKERS; j++) {
            a[i * NUM_WORKERS + j] = i * NUM_WORKERS + j;
            b[i * NUM_WORKERS + j] = 0;
        }
    }

    // Use the num_gangs clause to specify the number of gangs
    #pragma acc parallel num_gangs(NUM_GANGS)
    {
        // Use the num_workers clause to specify the number of workers
        #pragma acc loop num_workers(NUM_WORKERS)
        for (i = 0; i < NUM_GANGS; i++) {
            for (j = 0; j < NUM_WORKERS; j++) {
                b[i * NUM_WORKERS + j] = a[i * NUM_WORKERS + j];
            }
        }
    }

    // Check whether the specified number of gangs is used
    num_gangs = acc_get_num_gangs();
    if (num_gangs != NUM_GANGS) {
        printf("Error: expected %d gangs, but got %d\n", NUM_GANGS, num_gangs);
        return 1;
    }

    // Check whether the specified number of workers is used
    num_workers = acc_get_num_workers();
    if (num_workers != NUM_WORKERS) {
        printf("Error: expected %d workers, but got %d\n", NUM_WORKERS, num_workers);
        return 1;
    }

    // Check whether the arrays are equal
    for (i = 0; i < NUM_GANGS; i++) {
        for (j = 0; j < NUM_WORKERS; j++) {
            if (a[i * NUM_WORKERS + j] != b[i * NUM_WORKERS + j]) {
                printf("Error: arrays are not equal\n");
                return 1;
            }
        }
    }

    printf("Success: the specified number of gangs and workers are used\n");
    return 0;
}