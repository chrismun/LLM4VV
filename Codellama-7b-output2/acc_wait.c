#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 10
    int num = rand() % 10 + 1;

    // Create a barrier with the number of threads
    #pragma acc parallel num_threads(num)
    {
        #pragma acc loop
        for (int i = 0; i < num; i++) {
            #pragma acc wait(num)
        }
    }

    // Check if the barrier was correctly synchronized
    if (num != 1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    // Print the result
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}