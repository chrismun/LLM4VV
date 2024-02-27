#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Activate an OpenACC parallel region to ensure that an acc-device is present
#pragma acc parallel num_workers(1)
    {
        int default_async = acc_get_default_async();

        // Just for demonstration, the default returned should be 0 unless modified.
        // The specification does not dictate specific numbers for async queues,
        // but typically, the initial default is 0.
        if (default_async != 0) {
            // If not zero, this is unexpected in this specific test context
            err = 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}