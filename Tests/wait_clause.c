#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 10
    int x = rand() % 10 + 1;

    // Use the wait clause to wait for x seconds
    #pragma acc parallel wait(x)
    {
        // Do some work
        printf("Hello from thread %d\n", omp_get_thread_num());
    }

    // Check if the wait clause worked correctly
    if (omp_get_wtime() - x < 0.01) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test1();
    }

    // Check if any of the tests failed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}