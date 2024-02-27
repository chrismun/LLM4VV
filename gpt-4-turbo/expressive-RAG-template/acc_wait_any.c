#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc_wait_any, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int count = 2; // Number of async operations to test
    int wait_arg[] = {1, 2}; // Async handles
    int data[100];

    // Initialize some data to work on
    for(int i = 0; i < 100; ++i) {
        data[i] = i;
    }

    // Start two async operations on different queues
    #pragma acc parallel loop async(wait_arg[0])
    for (int i = 0; i < 50; ++i) {
        data[i] = data[i] * 2;
    }

    #pragma acc parallel loop async(wait_arg[1])
    for (int i = 50; i < 100; ++i) {
        data[i] = data[i] * 2;
    }

    // Wait for any of the above operations to complete
    int completed_queue = acc_wait_any(count, wait_arg);

    if(completed_queue < 0 || completed_queue >= count) {
        printf("acc_wait_any returned an invalid value: %d\n", completed_queue);
        err++;
    }

    // Verify that at least one of the operations has completed
    int found_incomplete = 0;
    for (int i = 0; i < 100; ++i) {
        if((i < 50 && wait_arg[0] == completed_queue && data[i] != i * 2) ||
           (i >= 50 && wait_arg[1] == completed_queue && data[i] != i * 2)) {
            found_incomplete = 1;
            break;
        }
    }

    if(found_incomplete) {
        printf("The operation on queue %d did not complete as expected.\n", completed_queue);
        err++;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}