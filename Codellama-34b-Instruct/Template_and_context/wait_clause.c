#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a parallel region with a wait clause
    #pragma acc parallel num_gangs(1) wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create a serial region with a wait clause
    #pragma acc serial wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create a kernels region with a wait clause
    #pragma acc kernels num_gangs(1) wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create a data region with a wait clause
    #pragma acc data wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create an enter data region with a wait clause
    #pragma acc enter data wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create an exit data region with a wait clause
    #pragma acc exit data wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    // Create an update directive with a wait clause
    #pragma acc update wait(1)
    {
        // Do some work
        printf("Hello from thread %d\n", acc_get_thread_num());
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}