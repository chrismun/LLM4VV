#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define NUM_GANGS 2510
#define NUM_WORKERS 1024
#define NUM_VECTORS 16

int main() {
    int failcode = 0;
    int failed;

    // Test 1: num_gangs clause on parallel construct
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int num_gangs = NUM_GANGS;
        int num_workers = NUM_WORKERS;
        int num_vectors = NUM_VECTORS;

        #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) num_vectors(num_vectors)
        {
            // Do some work
        }

        if (acc_get_num_gangs() != num_gangs) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: num_gangs clause on kernels construct
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int num_gangs = NUM_GANGS;

        #pragma acc kernels num_gangs(num_gangs)
        {
            // Do some work
        }

        if (acc_get_num_gangs() != num_gangs) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}