#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 5

int test1() {
    int err = 0;
    srand(SEED);
    int *a_host = (int *)malloc(sizeof(int)); 
    *a_host = 5; // Arbitrary value for testing
   
    // Initialize a data region on the device
    #pragma acc enter data create(a_host[0:1])

    // Try to use the present clause
    #pragma acc parallel present(a_host[0:1])
    {
        // Modify the value to see if it's actually shared
        if(*a_host != 5) {
            err = 1; // If it doesn't match, set an error
        }
        *a_host = 10; // Modify to verify write-back happens correctly
    }

    // Read back to host to verify write-back
    #pragma acc exit data copyout(a_host[0:1])

    if(*a_host != 10) {
        err = 1; // Error if value wasn't updated indicating data wasn't present properly
    }

    // Clean up
    free(a_host);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0); // Using bitwise operation to set failcode, useful for multiple tests
    }

    // For debugging purposes
    if(failcode != 0){
        printf("Test FAILED.\n");
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}