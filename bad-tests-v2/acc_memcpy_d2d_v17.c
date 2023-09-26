#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize the data
    int data_dest[10];
    int data_src[10];
    for (int i = 0; i < 10; i++) {
        data_dest[i] = rand();
        data_src[i] = rand();
    }

    // Copy the data from the source to the destination
    acc_memcpy_d2d(data_dest, data_src, 10, 0, 0);

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (data_dest[i] != data_src[i]) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the results
    if (failcode) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}