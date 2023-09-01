#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    int num_threads = 4;
    int num_iterations = 1000;

    #pragma acc parallel num_threads(num_threads)
    {
        #pragma acc loop
        for (int i = 0; i < num_iterations; i++) {
            int async_id = omp_get_thread_num() + 1;
            #pragma acc async async_id
            {
                #pragma acc loop
                for (int j = 0; j < num_iterations; j++) {
                    int x = rand() % 100;
                    #pragma acc wait async async_id
                }
            }
        }
    }

    #pragma acc wait async

    if (omp_get_num_threads() != num_threads) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel num_threads(NUM_TEST_CALLS)
    {
        #pragma acc loop
        for (int x = 0; x < NUM_TEST_CALLS; x++) {
            failed = failed + test1();
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}