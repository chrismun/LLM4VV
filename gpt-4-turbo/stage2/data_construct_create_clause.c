#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:data construct create clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *a_host = (int *)malloc(sizeof(int)); // Allocate memory on host
    *a_host = 1; // Initialize with any value to verify if it gets changed

    // Using OpenACC to allocate but not initialize 'a_device' on the device
    #pragma acc data create(a_host[0:1])
    {
        // Now, explicitly initialize 'a_host' on the device to a different value to check if create clause worked
        #pragma acc parallel present(a_host)
        {
            a_host[0] = 10;
        }
    }

    // Copy from device to host to validate the change
    #pragma acc update host(a_host[0:1])

    // If the create clause works, a_host should be 10
    if (*a_host != 10) {
        err += 1;
    }

    free(a_host); // Clean up
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    return failcode;
}