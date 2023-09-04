#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345
#define PRECISION 0.0001

int test_loop_gang_clause(int n, int num_gangs, int num_workers);

int main() {
    int failcode = 0;
    int failed;

    // Test loop gang clause with different values of n, num_gangs, and num_workers
    failed = test_loop_gang_clause(10, 2, 4);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    failed = test_loop_gang_clause(100, 4, 8);
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    failed = test_loop_gang_clause(1000, 8, 16);
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}

int test_loop_gang_clause(int n, int num_gangs, int num_workers) {
    int err = 0;
    srand(SEED);

    // Allocate memory for arrays
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Set up loop gang clause
    #pragma acc loop gang(num_gangs)
    for (int x = 0; x < n; ++x) {
        #pragma acc loop worker(num_workers)
        for (int y = 0; y < n; ++y) {
            b[x] += a[y];
        }
    }

    // Check results
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    // Free memory
    free(a);
    free(b);

    return err;
}