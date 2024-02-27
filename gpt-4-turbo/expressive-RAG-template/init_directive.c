#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Function to test OpenACC init directive
int test_init_directive(){
    int err = 0;
    bool runtime_initialised = false;

    // Use the OpenACC init directive to initialize runtime system for any available device type
    #pragma acc init

    // Attempt to execute a minimal OpenACC parallel region
    int testVal = 0;
    #pragma acc parallel reduction(+:testVal)
    {
        testVal += 1;
    }

    // If testVal is not incremented, it indicates failure in runtime system initialization
    if (testVal != 1) {
        fprintf(stderr, "OpenACC runtime system initialization failed.\n");
        err = 1; // Indicates an error
    } else {
        runtime_initialised = true;
    }

    // Optionally, verify device count for confirmation (not strictly necessary for init directive testing)
    if (runtime_initialised) {
        int num_devices = acc_get_num_devices(acc_device_not_host);
        if (num_devices <= 0) {
            fprintf(stderr, "No OpenACC devices found.\n");
            err = 1; // Indicates an error
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    srand(SEED);

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_init_directive();
    }

    if (failed != 0){
        failcode += 1; // If any of the test calls failed, set a non-zero fail code.
        printf("One or more tests failed.\n");
    } else {
        printf("All tests passed successfully.\n");
    }

    return failcode;
}