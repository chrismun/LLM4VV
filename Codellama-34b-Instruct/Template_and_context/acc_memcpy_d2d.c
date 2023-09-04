#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the source and destination data
    int src_data[10];
    int dest_data[10];
    for (int i = 0; i < 10; i++) {
        src_data[i] = rand() % 100;
        dest_data[i] = 0;
    }

    // Copy the data from the source to the destination
    acc_memcpy_d2d(dest_data, src_data, 10 * sizeof(int), 0, 0);

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (dest_data[i] != src_data[i]) {
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode != 0) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return 0;
}