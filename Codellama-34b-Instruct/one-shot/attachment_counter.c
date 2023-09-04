#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: attachment counter
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int *a = (int *)malloc(sizeof(int));
        int *b = (int *)malloc(sizeof(int));

        // Initialize data
        *a = 1;
        *b = 0;

        // Attach data to device
        #pragma acc enter data copyin(a[0:1])

        // Increment attachment counter
        #pragma acc atomic update
        a[0]++;

        // Detach data from device
        #pragma acc exit data delete(a[0:1])

        // Check if attachment counter was incremented correctly
        if (a[0] != 2) {
            err++;
        }

        // Check if data was copied correctly
        if (b[0] != 1) {
            err++;
        }

        // Free memory
        free(a);
        free(b);

        if (err != 0) {
            failed++;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}