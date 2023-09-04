#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    acc_init(acc_device_host);

    // Create a pointer to a variable in shared memory
    int *var = (int *)acc_malloc(sizeof(int));

    // Set the value of the variable in shared memory
    *var = 123;

    // Create a present clause
    acc_present(var);

    // Check if the variable is in shared memory
    if (acc_is_present(var)) {
        printf("Variable is in shared memory\n");
    } else {
        printf("Variable is not in shared memory\n");
        err = 1;
    }

    // Free the memory allocated for the variable
    acc_free(var);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode == 0){
        printf("All tests passed\n");
    } else {
        printf("Some tests failed\n");
    }

    return failcode;
}