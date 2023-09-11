#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4;
    int num_threads = 8;
    int num_workers_per_thread = num_workers / num_threads;

    #pragma acc serial num_workers(num_workers)
    {
        int i;
        for (i = 0; i < num_workers; i++) {
            printf("Worker %d: Hello from worker %d\n", i, i);
        }
    }

    #pragma acc serial num_workers(num_workers_per_thread)
    {
        int i;
        for (i = 0; i < num_workers_per_thread; i++) {
            printf("Worker %d: Hello from worker %d\n", i, i);
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}