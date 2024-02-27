#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define constants for the test
#define SEED 12345
#define NUM_TEST_CALLS 1

#ifndef T1
// T1: data construct copy clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize a test variable.
    int host_var = rand() % 100;  // Random integer between 0 and 99.
    int original_value = host_var;

    // Perform the copy to and from the device, modifying the variable on the device.
    #pragma acc data copy(host_var)
    {
        #pragma acc parallel
        {
            // Modify the variable on the device
            host_var += 5;
        }
    }
    // Check if the modification made on the device is reflected back on the host.
    if (host_var != original_value + 5) {
        printf("Error: host_var expected to be %d but was %d.\n", original_value + 5, host_var);
        err = 1;  // Indicate an error.
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("Test Passed.\n");
    } else {
        printf("Test Failed.\n");
    }
    return failcode;
}